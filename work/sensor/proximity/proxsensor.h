#include "Zumo32U4ProximitySensors.h"

class proxSensor {
public:
  // Empty Initialize
  proxSensor();

  // Pass through sensor
  proxSensor(Zumo32U4ProximitySensors);

  // Basic read, 
  bool basicReadClose();
  int deepRead();

private:
  Zumo32U4ProximitySensors _proxSensor;
};

#include "proxsensor.cpp"
