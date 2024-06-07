#include "../headers.hpp"
#include "MotorController.h"



MotorController::MotorController() {}


void MotorController::setSpeed(int newLeft, int newRight){
  newLeft = constrain(newLeft, -350, 350);
  newRight = constrain(newRight, -350, 350);
  motors.setSpeeds(newLeft, newRight);
}

motorSpeeds MotorController::read() {
  return { OCR1B, OCR1A };
}

void MotorController::stop(){
  motors.setSpeeds(0, 0);
}

