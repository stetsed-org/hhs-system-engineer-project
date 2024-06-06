#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "../headers.hpp"

class navigator {
public:
  pathFindingData pathFindingBlack(sensorStruct*, int,int*,int);
  pathFindingData pathFindingTurn(sensorStruct*);
  pathFindingData pathFindingGreen(sensorStruct*, int,int*);
};

#include "navigator.cpp"

#endif
