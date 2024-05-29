#ifndef PROXSENSOR_H
#define PROXSENSOR_H

#include "Zumo32U4ProximitySensors.h"

/** Class for reading the Proximity Sensor and returning Usable Data
 * To-do: Subclass of eventual "Sensor" baseclass, implement later.
*/
class proxSensor {
public:
  /** proxSensor constructor without input 
    * Only used within global variable decleration, not used outside. 
  */
  proxSensor();

  /** proxSensor constructor with Proximity Sensor Instance
    * Get's given an instance of Zumo32U4ProximitySensors, due to issues when
    * initializing inside of the Constructor itself.
  */
  proxSensor(Zumo32U4ProximitySensors*);

  /** Perform a basic read
    *  Returns back Boolean if >= 50(?)cm in distance, otherwise return false.
    *  Uses the default Zumo32U4ProximitySensors.read function provided by 32U4 library.
    *  If debug global var is true, shall return number of sensors active and the raw data to Serial1 
  */
  bool basicReadClose();
  // Advanced Read, currently unused, possibly will return int of distance if able to acces > 1 prox sensor and/or read analog data.
  int deepRead();

private:
  Zumo32U4ProximitySensors* pvt_proxSensor;
};

#include "proxsensor.cpp"

#endif
