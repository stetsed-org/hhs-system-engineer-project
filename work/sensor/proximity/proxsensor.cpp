#include "Zumo32U4ProximitySensors.h"
#include "WString.h"
#include "HardwareSerial.h"
#include <Arduino.h>

proxSensor::proxSensor() {
}

proxSensor::proxSensor(Zumo32U4ProximitySensors a) : pvt_proxSensor(a) {

}

bool proxSensor::basicReadClose() {
  if (debug) {
    Serial1.println("Number of Sensors Active: " + String(pvt_proxSensor.getNumSensors()));
  }
  pvt_proxSensor.read();
  int leftled = pvt_proxSensor.countsFrontWithLeftLeds();
  int rightled = pvt_proxSensor.countsFrontWithRightLeds();

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
