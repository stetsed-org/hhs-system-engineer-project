#include "Zumo32U4ProximitySensors.h"

/** Class for reading the Proximity Sensor and returning Usable Data
 * To-do: Subclass of eventual "Sensor" baseclass, implement later.
*/
class proxSensor {
public:
  // Empty Initialize
  proxSensor();

  // Initialize Class with an instacen of the Proximity Sensor Class Zumo32U4ProximitySensors
  proxSensor(Zumo32U4ProximitySensors);

  // Basic read, returns boolean if closer than 50(?)cm infront of the Zumo
  bool basicReadClose();
  // Advanced Read, currently unused, possibly will return int of distance if able to acces > 1 prox sensor and/or read analog data.
  int deepRead();

private:
  Zumo32U4ProximitySensors pvt_proxSensor;
};

#include "proxsensor.cpp"
