#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "../headers.hpp"

class navigator {
private:
bool TL = false;
bool TR = false;
bool LineGone = false;
unsigned int lastTime = 0;
unsigned int turnTime = 0;
unsigned int lastLeft = 0;
unsigned int lastRight = 0;
int howLongTurn = 200;
int howLongReset = 250;
int turnSpeedLeft = -3000;
int turnSpeedRight = 5000;

public:
  pathFindingData pathFindingBlack(sensorStruct*, int,int*,int);
  pathFindingData pathFindingTurn(sensorStruct*);
  pathFindingData pathFindingGreen(sensorStruct*, int,int*,int);
};

#include "navigator.cpp"

#endif
