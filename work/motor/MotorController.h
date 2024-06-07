
#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "../headers.hpp"

struct motorSpeeds {
  uint16_t left, right;
};

class MotorController : public Sensor {
  private:
    Zumo32U4Motors motors;

  public:
    MotorController();
    motorSpeeds read();
    void setSpeed(int, int);
    void stop();
};

#include "MotorController.cpp"

#endif

