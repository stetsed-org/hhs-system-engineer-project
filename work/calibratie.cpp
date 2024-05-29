#include "Zumo32U4Motors.h"
#include <Arduino.h>
#include "sensor/encoders/encoders.h"
#include <string.h>

float calibrateMotor(Zumo32U4Motors motor, int Speed, CompatibleEncoders encoder){
  encoder.ResetValues();

  float offset = 0;

  motor.setLeftSpeed(Speed);
  motor.setRightSpeed(Speed);


  int32_t leftvalue = encoder.ReadLeft();
  int32_t rightvalue = encoder.ReadRight();

  motor.setLeftSpeed(0);
  motor.setRightSpeed(0);

  if (leftvalue > rightvalue){
      float offset = rightvalue / leftvalue;
  }
  else if (rightvalue > leftvalue){
      float offset = leftvalue / rightvalue;
  }
  if (rightvalue == leftvalue){
    float offset = 0.0;
  }

  return offset;
}
