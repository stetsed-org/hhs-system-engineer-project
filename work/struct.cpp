#ifndef STRUCT_CPP
#define STRUCT_CPP

#include <Arduino.h>
#include <Zumo32U4.h>
#include "headers.hpp"

struct {
  bool leftTurnActive;
  bool rightTurnActive;
  char currentColor;
} stateStorageStruct;

struct{
  proxSensor* proximitySensorPointer;
  // lineSensor lineSensorPointer;
  Accelerometer* accelerometerPointer;
  Gyroscope* gyroscopePointer;
  Magnetometer* magnetometerPointer;
  CompatibleEncoders* encodersPointer;

} sensorStruct;


#endif
