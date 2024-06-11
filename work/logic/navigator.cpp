#ifndef NAVIGATOR_CPP
#define NAVIGATOR_CPP

#include "../headers.hpp"
#include <HardwareSerial.h>

char colorDetection(sensorStruct* sensorStructPointer, int* lineSensorValues){
    //sensorStructPointer -> lineSensorPointer -> readCalibrated(lineSensorValues);
    // Left Middle * 0.25 + Middle + Right Middle * 0.25
    int value = (int)(lineSensorValues[2]);
    //Serial1.println((String)value);
    //Serial1.println("Value: " + (String)value);

    if ((75 < value) && (value < 175)){
        //Serial1.println("Color is green?");
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

pathFindingData navigator::pathFindingOnColor(lineColor color, sensorStruct* sensorStructObject, int lastError, int* lineSensorValues){
  // Defining a max speed for the motors, can be a value between 0-400, caution against setting to high incase of motor damage. 
  pathFindingData pathFindingDataInstance;
  unsigned long currentTime = millis();
  int timeAddition, X, maxSpeed, mincolour;
  static bool LineGoneLeft, LineGoneRight;
  static int turnTimeLeft, turnTimeRight;
  // Reading the lineSensor's with readLine which returns a value between 0-4000
  int position = sensorStructObject -> lineSensorPointer -> readLine_but_good_and_not_colour_blind(lineSensorValues, 1);

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
  
  if ((lineSensorValues[0] > mincolour) && !TL) {TL = true; lastLeft = currentTime;}
  if ((lineSensorValues[4] > mincolour) && !TR) {TR = true; lastRight = currentTime;}

  //we have detetectd a turn, we are on a line, the reset time has pased
  if (TL && (position >= 0) && ((currentTime - lastLeft) > howLongReset)){
    TL = false;
    lastLeft = 0;
  }
  if (TR && (position >= 0) && ((currentTime - lastRight) > howLongReset)){
    TR = false;
    lastRight = 0;
  }

  if (position == -4200){ //it's not on line
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
    //we are on a line, we have a turn, turning for so long?, we don't have a line
  else 
  {
    if (TL && TR) TL=false,TR=false;
    if (TL && (currentTime > (turnTimeLeft + howLongTurn)) && LineGoneLeft) TL = false, LineGoneLeft = false;
    
    if (TR && (currentTime > (turnTimeRight + howLongTurn)) && LineGoneRight) TR = false, LineGoneRight = false;

  }

  int error = position - 1000;

  int proportional = 2;
  int derivitave = 1;

  //PD
  int speedDiffrence = error * proportional + derivitave * (error - lastError);

  //speedDiffrence /= 5;
  pathFindingDataInstance.currentError = error;
  pathFindingDataInstance.leftMotorSpeed = maxSpeed - X + map(speedDiffrence, -800, 800, -X, X);
  pathFindingDataInstance.rightMotorSpeed = maxSpeed - X + map(-speedDiffrence, -800, 800, -X, X); 
  
  pathFindingDataInstance.currentColor = colorDetection(sensorStructObject, lineSensorValues);
  return pathFindingDataInstance;
}

bool navigator::bonkthebox(sensorStruct* sensorStructPointer, Zumo32U4Motors* motorPointer,int* lineSensorValues ){
  if (!bonkHasRan){
    motorPointer -> setSpeeds(200,200);
    delay(1500);
    motorPointer -> setSpeeds(0,0);
    bonkHasRan = false;

  }
  
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
