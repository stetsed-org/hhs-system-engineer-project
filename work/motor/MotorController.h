
#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "../headers.hpp"



class MotorController{
    private:
    int leftSpeed;
    int rightSpeed;
    Zumo32U4Motors motors;


    public:
    MotorController();
    ~MotorController();

    void setSpeed(int, int);
    void stop();
};

#include "MotorController.cpp"

#endif

