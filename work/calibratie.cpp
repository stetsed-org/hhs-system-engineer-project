#ifndef CALIBRATIE_CPP
#define CALIBRATIE_CPP

#include "Zumo32U4Motors.h"
#include <Arduino.h>
#include "sensor/encoders/encoders.h"
#include <string.h>


/*
 Motor calibration function, takes in motor, speed and an instance of the compatible encoders(switch to sensorStruct later).
 Returns a float which is the offset which should be used inside of the motors.
*/
float calibrateMotor(Zumo32U4Motors motor, int Speed, CompatibleEncoders encoder){
  
  /*
   Reset the encoder values, then set the motors to go at the wanted speed,
   read the encoders and turn off the motors then calculate the offset.
  */
  encoder.ResetValues();

  float offset = 0;

  motor.setLeftSpeed(Speed);
  motor.setRightSpeed(Speed);

  delay(10000);

  int leftvalue = encoder.ReadLeft();
  int rightvalue = encoder.ReadRight();
  Serial1.println(leftvalue);
  Serial1.println(rightvalue);

  motor.setLeftSpeed(0);
  motor.setRightSpeed(0);

  /* Calculates the offset by dividing whatever side is lower to get a number
     between 0-1. Then makes this value negative if it's an offset for the rightside.

     If the left spins 10% faster, it will be 100 / 110 which is ~0.9 
     this means we want to spin the left one with a factor of 0.9

     If the right spins 10% faster it will be 100/110 * -1, which is -0.9
     which we then use to make the right one spin 10% slower.

     If they both spin the same speed then offset will be 1 which means
     we make no changes to the speed values of either side.
  */
  if (leftvalue > rightvalue){
      offset = (float)rightvalue / (float)leftvalue;
  }
  else if (rightvalue > leftvalue){
      offset = (float)leftvalue / (float)rightvalue;
      offset *= -1;
  }
  if (rightvalue == leftvalue){
    offset = 1;
  }

  return offset;
}

#endif
