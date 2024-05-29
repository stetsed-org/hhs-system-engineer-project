#ifndef HEADERS_HPP 
#define HEADERS_HPP 
#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <string.h>
#include "serial/serial.cpp"

// Include Encoders
#include "sensor/encoders/encoders.h"

// Include proximity sensor
#include "sensor/proximity/proxsensor.h"

// Include Compass Based Sensors
#include "sensor/compass/gyroscope/gyro.h"
#include "sensor/compass/magnetometer/magnet.h"
#include "sensor/compass/accelerometer/accel.h"

// Include line sensors
#include "sensor/line/linesensors.h"

// Include Calibration and others
#include "calibratie.cpp"
#include "ran-func.cpp"
#include "struct.cpp"

#endif
