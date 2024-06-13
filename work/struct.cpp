#ifndef STRUCT_CPP
#define STRUCT_CPP

#include <Arduino.h>
#include <Zumo32U4.h>
#include "headers.hpp"

// Struct designed to store the current State of the program
struct stateStorageStruct{
  bool leftTurnActive;
  bool rightTurnActive;
  char currentColor[10] = {'b','b','b','b','b','b','b','b','b','b'};
};

// Struct designed to store all the sensors we have available to easily pass to program
struct sensorStruct{
  proxSensor* proximitySensorPointer;
  linesensors* lineSensorPointer;
  Accelerometer* accelerometerPointer;
  Gyroscope* gyroscopePointer;
  Magnetometer* magnetometerPointer;
  CompatibleEncoders* encodersPointer;

} ;

// Struct that returns from pathFinding with wanted data
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
