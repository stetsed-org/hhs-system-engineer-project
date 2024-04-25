#include "headers.hpp"

class proxSensor {
public:
  // Boolean input, if it is true enable all sensors, if false enable front
  // sensor
  proxSensor(bool);

private:
  bool _enableAll;
  Zumo32U4ProximitySensors _proxSensor;
};
