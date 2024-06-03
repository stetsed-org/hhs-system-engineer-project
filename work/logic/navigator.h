#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "../headers.hpp"

class navigator {
public:
  pathFindingData pathFindingBlack(sensorStruct*, int,int*);
  pathFindingData pathFindingTurn(sensorStruct*);
  pathFindingData pathFindingGreen(sensorStruct*);
};

#include "navigator.cpp"

#endif
