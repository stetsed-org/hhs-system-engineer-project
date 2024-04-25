#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>

#include "proxsensor.h"

proxSensor::proxSensor(bool a) : _enableAll(a) {
  if (_enableAll) {
    _proxSensor = Zumo32U4ProximitySensors();
    _proxSensor.initThreeSensors();
  } else {
    _proxSensor = Zumo32U4ProximitySensors();
    _proxSensor.initFrontSensor();
  }
}
