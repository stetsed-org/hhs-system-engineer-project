#ifndef NAVIGATOR_CPP
#define NAVIGATOR_CPP

#include "../headers.hpp"
#include <HardwareSerial.h>

// Function designed to differentiate the color of the diffrent lines,
// values are calibrated based on full battery measurment, all same logic
// except that brown will first check center sensor and if that is correct
// check others as brown is solid line and avoids un-needed comparison operations.
char colorDetection(sensorStruct* sensorStructPointer, int* lineSensorValues){
    int value = (int)(lineSensorValues[2]);

    if ((75 < value) && (value < 175)){
        return 'g';
    }

    else if (value > 700 && value < 800){
      int BrownState = 0;
      for (int i = 0; i < 5; ++i){
        if(lineSensorValues[i] > 420 && lineSensorValues[i] < 810){
          BrownState++;
        }
      }
      if (BrownState > 3){
        return 'r';
      }
      else{
        return 'n';
      }
    }
    else if (value > 900) {
      return 'b';
    }

    return 'n';
  }

pathFindingData navigator::pathFindingOnColor(lineColor color, sensorStruct* sensorStructObject, int lastError, int* lineSensorValues, SerialJSON* xbeePointer){
  // Instantiate the wanted variables, millis retrieves current time in milliseconds
  pathFindingData pathFindingDataInstance;
  unsigned long currentTime = millis();
  int timeAddition, X, maxSpeed, mincolour;
  static bool LineGoneLeft, LineGoneRight;
  static int turnTimeLeft, turnTimeRight;
  // Reading the lineSensor's with customized readLine function to return color values
  // that can be used inside of our program to differentiate White, Green, Black etc.
  int position = sensorStructObject -> lineSensorPointer -> readLine_but_good_and_not_colour_blind(lineSensorValues, 1);
  xbeePointer ->addNewData("lineData",lineSensorValues, 5);

  // Set our variables depending on what color enum was given.
  switch (color) {
    case lineColor::Black:
      X = 110;
      maxSpeed = 350;
      howLongReset = 200;
      mincolour = 600;
      break;
    
    case lineColor::Green:
      X = 75;
      maxSpeed = 200;
      howLongReset = 300;
      mincolour = 125;
      break;
  }
  /*Check the left and right sensor to see if there is a right turn or
  * a left turn available, and if it's not already set then we set it and set that
  * we saw that turn (lastLeft/lastRight) to the currentTime.
  */
  if ((lineSensorValues[0] > mincolour) && !TL) {TL = true; lastLeft = currentTime;}
  if ((lineSensorValues[4] > mincolour) && !TR) {TR = true; lastRight = currentTime;}

  /* We did detect a turn, but we are still on the line and the reset timer
  * has passed, this let's us assume that we didn't need to take it and as such
  * reset the turn state.
  */
  if (TL && (position >= 0) && ((currentTime - lastLeft) > howLongReset)){
    TL = false;
    lastLeft = 0;
  }
  if (TR && (position >= 0) && ((currentTime - lastRight) > howLongReset)){
    TR = false;
    lastRight = 0;
  }
  
  /* ReadLine returns -4200 only if we have completley lost line as a value of 
  * -4200 should be impossible otherwise, it then checks if we have a turn and if so set
  *  the wanted speed to be able to make an angled turn.
  */ 
  if (position == -4200){
      position = 1000; 
      if (TR && !LineGoneLeft) turnTimeLeft = currentTime, LineGoneLeft = true;
      

      if (TL && !LineGoneRight) turnTimeRight = currentTime, LineGoneRight = true; 
      

      if(TL && !TR) {
        position = turnSpeedLeft;
      }
      else if(TR && !TL) {
        position = turnSpeedRight;
      }
    }
  else 
  {
    // Both turn right and turn left should never both be true, if they are reset
    if (TL && TR) TL=false,TR=false;
    // These check if we have turned for X amount of time, where X is set by what color we are on.
    if (TL && (currentTime > (turnTimeLeft + howLongTurn)) && LineGoneLeft) TL = false, LineGoneLeft = false;
    
    if (TR && (currentTime > (turnTimeRight + howLongTurn)) && LineGoneRight) TR = false, LineGoneRight = false;

  }

  /* PID Controller implementation, to avoid constantly going right left right left
   * it makes gradual adjuments by taking in the current error, the last error
   * and our proportional/derivitave variables.
    */
  int error = position - 1000;
  int proportional = 2;
  int derivitave = 1;
  int speedDiffrence = error * proportional + derivitave * (error - lastError);
  xbeePointer->addNewData("speedDifference", speedDiffrence);
  /* Set the return data to be the error to return as the currentError,
   * and map speeds to be a value we can use on the motors
   * speedDiffrence is decided by the PID and X is decided by color
   * larger X means larger correction but less often, smaller X means smaller
   * corrections but more often, -800 800 means it will assume
   * the max it can be given is 800 and the minimum is -800 and will map according
   * to this
  */
  pathFindingDataInstance.currentError = error;
  pathFindingDataInstance.leftMotorSpeed = maxSpeed - X + map(speedDiffrence, -800, 800, -X, X);
  pathFindingDataInstance.rightMotorSpeed = maxSpeed - X + map(-speedDiffrence, -800, 800, -X, X); 
  
  // Runs color detection function to return to the main function inside of the return data
  pathFindingDataInstance.currentColor = colorDetection(sensorStructObject, lineSensorValues);
  return pathFindingDataInstance;
}

bool navigator::bonkthebox(sensorStruct* sensorStructPointer, Zumo32U4Motors* motorPointer,int* lineSensorValues ){
  // Check if we have already ran this function 1 time, if no then we first drive into the middle of the circle
  if (!bonkHasRan){
    motorPointer -> setSpeeds(200,200);
    delay(1500);
    motorPointer -> setSpeeds(0,0);
    bonkHasRan = false;

  }
  
  /* Self contained loop, we check the proxmity sensors while spinning in a circle,
   * if we get a signal that it's close enough we sprint ahead and start pushing the box.
   * And we check the line sensor to see if we have hit the line which means we have pushed
   * the box far enough and we can exit the loop.
  */
  while (true) {
    bool read = sensorStructPointer ->proximitySensorPointer ->read();
    sensorStructPointer ->lineSensorPointer ->readLine(lineSensorValues);
    if (lineSensorValues[2] > 20){
      return true;
    }
    if (read){
      Serial1.println("BONK IT");
      motorPointer -> setSpeeds(250,250);
      }
    else{
      Serial1.println("Enemy not spotted");
      motorPointer -> setSpeeds(-250,250);
    }
  }
}

#endif // !NAVIGATOR_CPP
