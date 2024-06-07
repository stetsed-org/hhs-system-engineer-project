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
int howLongTurn = 100;
int howLongReset = 200;
int turnSpeedLeft = -2000;
int turnSpeedRight = 4000;

public:
  pathFindingData pathFindingBlack(sensorStruct*, int,int*,int);
  pathFindingData pathFindingTurn(sensorStruct*);
  pathFindingData pathFindingGreen(sensorStruct*, int,int*,int);
};

#include "navigator.cpp"

#endif
