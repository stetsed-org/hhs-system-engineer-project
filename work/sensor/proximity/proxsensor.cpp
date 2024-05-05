#include "Zumo32U4ProximitySensors.h"
#include "WString.h"
#include "HardwareSerial.h"
#include <Arduino.h>

/** proxSensor constructor without input 
 * Only used within global variable decleration, not used outside. 
*/
proxSensor::proxSensor() {
}

/** proxSensor constructor with Proximity Sensor Instance
 * Get's given an instance of Zumo32U4ProximitySensors, due to issues when
 * initializing inside of the Constructor itself.
*/
proxSensor::proxSensor(Zumo32U4ProximitySensors a) : pvt_proxSensor(a) {

}

/** Perform a basic read
 *  Returns back Boolean if >= 50(?)cm in distance, otherwise return false.
 *  If debug global var is true, shall return number of sensors active and the raw data to Serial1 
*/
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

// Advanced Read, currently unused, possibly will return int of distance if able to acces > 1 prox sensor and/or read analog data.
int proxSensor::deepRead() {
  Serial1.println("This is not yet implemented,future me's problem");
}
