#ifndef NAVIGATOR_CPP
#define NAVIGATOR_CPP

#include "../headers.hpp"

char colorDetection(sensorStruct* sensorStructPointer, int* lineSensorValues){
    sensorStructPointer -> lineSensorPointer -> readCalibrated(lineSensorValues);
    // Left Middle * 0.25 + Middle + Right Middle * 0.25
    int value = (int)(lineSensorValues[1] + lineSensorValues[2] + lineSensorValues[3]);
    Serial1.println((String)value);
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

  pathFindingData pathFindingDataInstance;

  // Reading the lineSensor's with readLine which returns a value between 0-4000
  int position = sensorStructObject -> lineSensorPointer -> readLine(lineSensorValues);

  // Subtract 2000, so a negative number means we need to go left and a positive number means we need to go right
  int error = position - 1500;

  /* PID Controller, you can set proportional value and derivitave value to diffrent settings
    * Default values: 4, 6
    * Default values have been chosen because they seemed to give a good balance between accuracy of following the line
    * And of speed.
    *
    * And with these values, the current error value and the previous error value given to the function, which is
    * stored in stateStorage struct for the program. And the defined values it will calculate the speed
    * differentional
    */
  int proportional = 4;
  int derivitave = 6;

  int speedDiffrence = error / proportional + derivitave * (error - lastError);

  pathFindingDataInstance.currentError = error;

  int tempLeftMotorSpeed = maxSpeed + speedDiffrence;
  int tempRightMotorSpeed = maxSpeed - speedDiffrence;

  /* Makes sure we are not given a value lower than 0 and 
   * higher than maxspeed to the motors for return.
  *
  */
  pathFindingDataInstance.leftMotorSpeed = constrain(tempLeftMotorSpeed, 0,maxSpeed);
  pathFindingDataInstance.rightMotorSpeed = constrain(tempRightMotorSpeed,0,maxSpeed);

  /* Return an instance of the pathFindingData struct, which is a struct designed 
   * to return data for this function which has the most recent error value, 
   * and the speeds the motors are wanted.
    */

  //pathFindingDataInstance.currentColor = 
 
  pathFindingDataInstance.currentColor = colorDetection(sensorStructObject, lineSensorValues);
  return pathFindingDataInstance;
}
#endif // !NAVIGATOR_CPP
