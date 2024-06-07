#ifndef NAVIGATOR_CPP
#define NAVIGATOR_CPP

#include "../headers.hpp"
#include <HardwareSerial.h>

char colorDetection(sensorStruct* sensorStructPointer, int* lineSensorValues){
    //sensorStructPointer -> lineSensorPointer -> readCalibrated(lineSensorValues);
    // Left Middle * 0.25 + Middle + Right Middle * 0.25
    int value = (int)(lineSensorValues[1] + lineSensorValues[2] + lineSensorValues[3]);
    //Serial1.println((String)value);
    //Serial1.println("Value: " + (String)value);

    if (value < 800){
        //Serial1.println("Color is green?");
        return 'g';
      }
    
    //else if (value > 400 && value < 500){
    //    Serial1.println("Color is probally gray");
    //    return 'y';
    //}
    else if (value >= 800){  
        //Serial1.println("Color is probally black");
        return 'b';
      }

    else {
      return 'b';
    }
  }


pathFindingData navigator::pathFindingBlack(sensorStruct* sensorStructObject, int lastError, int* lineSensorValues, int maxSpeed){
  // Defining a max speed for the motors, can be a value between 0-400, caution against setting to high incase of motor damage. 
  long currentTime = millis();
  pathFindingData pathFindingDataInstance;

  // Reading the lineSensor's with readLine which returns a value between 0-4000
  int position = sensorStructObject -> lineSensorPointer -> readLine_but_good_and_not_colour_blind(lineSensorValues);
  if (position < 0){ 
      position = 1000; 
      LineGone = true; 
      if(TL) {
        position = 0;
      }
      if(TR) {
        position = 2000;
      }
    }
  //else if (TL || TR) TL = false, TR = false;
  if (lineSensorValues[0] > 800) TL = true;
  if (lineSensorValues[4] > 800) TR = true;

  // if(lineSensorValues[0] >= 800) TL = true, Serial1.println("T-l");
  // if(lineSensorValues[4] >= 800) TR = true, Serial1.println("T-r");
  //if (LineGone) position = 2000;


  //Serial1.println(position);

  // Subtract 2000, so a negative number means we need to go left and a positive number means we need to go right
  int error = position - 1000;

  /* PID Controller, you can set proportional value and derivitave value to diffrent settings
    * Default values: 4, 6
    * Default values have been chosen because they seemed to give a good balance between accuracy of following the line
    * And of speed.
    *
    * And with these values, the current error value and the previous error value given to the function, which is
    * stored in stateStorage struct for the program. And the defined values it will calculate the speed
    * differentional
    */
  int proportional = 2;
  int derivitave = 1;

  int speedDiffrence = error * proportional + derivitave * (error - lastError);

  //speedDiffrence /= 5;
  pathFindingDataInstance.currentError = error;

  int tempLeftMotorSpeed = maxSpeed + speedDiffrence;
  int tempRightMotorSpeed = maxSpeed - speedDiffrence;
  
  //if (speedDiffrence == 0) speedDiffrence = maxSpeed; 
  /* Makes sure we are not given a value lower than 0 and 
   * higher than maxspeed to the motors for return.
  *
  */

  // if(speedDiffrence > 0){ //we should go to the right

  // } else if(speedDiffrence < 0){ //we should go to the left

  // } else{ //we should be going straight
  //   pathFindingDataInstance.leftMotorSpeed = max
  //   pathFindingDataInstance.rightMotorSpeed
  // }
                                                                //was 12000
  pathFindingDataInstance.leftMotorSpeed = maxSpeed/2 + map(speedDiffrence, -800, 800, -maxSpeed/2, maxSpeed/2);
  pathFindingDataInstance.rightMotorSpeed = maxSpeed/2 + map(-speedDiffrence, -800, 800, -maxSpeed/2, maxSpeed/2);

  // pathFindingDataInstance.leftMotorSpeed = speedDiffrence;
  // pathFindingDataInstance.rightMotorSpeed = speedDiffrence;

  // -50 < pathFindingDataInstance.leftMotorSpeed < 50? : pathFindingDataInstance.leftMotorSpeed = maxSpeed;
  // -50 < pathFindingDataInstance.rightMotorSpeed < 50? : pathFindingDataInstance.rightMotorSpeed = maxSpeed;

  // Serial1.print(position);
  // Serial1.print("\t, ");
  Serial1.print("PID:");
  // Serial1.print("\t, ");
  Serial1.print(speedDiffrence);
  Serial1.print(",");
  Serial1.print("const:");
  // Serial1.print(",");
  Serial1.println(0);
  /* Return an instance of the pathFindingData struct, which is a struct designed 
   * to return data for this function which has the most recent error value, 
   * and the speeds the motors are wanted.
    */

  //pathFindingDataInstance.currentColor = 
  long lastTime = currentTime;
  pathFindingDataInstance.currentColor = colorDetection(sensorStructObject, lineSensorValues);
  return pathFindingDataInstance;
}
#endif // !NAVIGATOR_CPP
