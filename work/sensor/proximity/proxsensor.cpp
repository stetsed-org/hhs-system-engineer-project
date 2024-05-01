#include "Zumo32U4ProximitySensors.h"
#include "WString.h"
#include "HardwareSerial.h"
#include <Arduino.h>

// Initialize for Global Variable
proxSensor::proxSensor() {
}

// Initialize while giving it the ZumoProxmitySensor which has to be preinitialized
proxSensor::proxSensor(Zumo32U4ProximitySensors a) : _proxSensor(a) {

}

bool proxSensor::basicReadClose() {
  //Serial1.println("Number of Sensors Active: " + String(_proxSensor.getNumSensors()));
  _proxSensor.read();
  int leftled = _proxSensor.countsFrontWithLeftLeds();
  int rightled = _proxSensor.countsFrontWithRightLeds();

  if (debug) {
  Serial1.println("Data L: " + String(leftled));
  Serial1.println("Data R: " + String(rightled));
  }

  if (leftled > 4 && rightled > 4){
    return true;
  }
  else {
    return false;
  }

}

int proxSensor::deepRead() {
  Serial1.println("This is not yet implemented,future me's problem");
}
