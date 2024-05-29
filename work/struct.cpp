#ifndef STRUCT_CPP
#define STRUCT_CPP

#include <Arduino.h>
#include <Zumo32U4.h>
#include "headers.hpp"

struct stateStorageStruct{
  bool leftTurnActive;
  bool rightTurnActive;
  char currentColor;
} ;

struct sensorStruct{
  proxSensor* proximitySensorPointer;
  linesensors* lineSensorPointer;
  Accelerometer* accelerometerPointer;
  Gyroscope* gyroscopePointer;
  Magnetometer* magnetometerPointer;
  CompatibleEncoders* encodersPointer;

} ;


#endif
