#ifndef STRUCT_CPP
#define STRUCT_CPP

#include <Arduino.h>
#include <Zumo32U4.h>
#include "headers.hpp"

struct stateStorageStruct{
  bool leftTurnActive;
  bool rightTurnActive;
  char currentColor[5] = {'b','b','b','b','b'};
} ;

struct sensorStruct{
  proxSensor* proximitySensorPointer;
  linesensors* lineSensorPointer;
  Accelerometer* accelerometerPointer;
  Gyroscope* gyroscopePointer;
  Magnetometer* magnetometerPointer;
  CompatibleEncoders* encodersPointer;

} ;

struct pathFindingData{
  int leftMotorSpeed;
  int rightMotorSpeed;
  int currentError;
  char currentColor;
};

enum class lineColor {
  Black,
  Green,
  Brown
};

#endif
