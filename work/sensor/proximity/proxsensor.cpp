#include "Zumo32U4ProximitySensors.h"
#include "WString.h"
#include "HardwareSerial.h"
#include <Arduino.h>

proxSensor::proxSensor(bool a) : _enableAll(a) {
  if (_enableAll) {
    Zumo32U4ProximitySensors _proxSensor = Zumo32U4ProximitySensors(); 
    _proxSensor.initThreeSensors();
  } else {
    uint8_t pins[] = "22";
    Zumo32U4ProximitySensors _proxSensor = Zumo32U4ProximitySensors();
    _proxSensor.init(pins,1,11);
  }
}

bool proxSensor::basicRead() {
  Serial1.println("Hello" + String(_proxSensor.getNumSensors()));
  _proxSensor.read();
  int leftled = _proxSensor.countsFrontWithLeftLeds();
  int rightled = _proxSensor.countsFrontWithRightLeds();

  Serial1.println("DT: " + String(leftled) + String(rightled));

  return true;
  
}

int proxSensor::deepRead() {
  Serial1.println("This is not yet implemented,future me's problem");
}
