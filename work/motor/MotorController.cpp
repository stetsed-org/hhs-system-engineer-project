#include "../headers.hpp"
#include "MotorController.h"



MotorController::MotorController(){
    leftSpeed = 0;
    rightSpeed = 0;
    Serial1.println("Object gemaakt");
}

MotorController::~MotorController(){
    Serial1.println("Ojbect gedeconstrueerd");
}


void MotorController::setSpeed(int leftSpeed, int rightSpeed){
    motors.setSpeeds(leftSpeed, rightSpeed);
}

void MotorController::stop(){
    motors.setSpeeds(0, 0);
}

