#include "Zumo32U4ProximitySensors.h"

class proxSensor {
public:
  // Boolean input, if it is true enable all sensors, if false enable front
  // sensor
  proxSensor(bool);

  bool basicRead();
  int deepRead();

private:
  bool _enableAll;
  Zumo32U4ProximitySensors _proxSensor;
};

#include "proxsensor.cpp"
