#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "../headers.hpp"
/* Class used inside of the main logic loop to decide where and how much to turn
  * contains logic for once passing brown line hitting the box out of the circle,
  * navigating on a color and navigating a turn.
*/

class navigator {
private:
bool TL = false;
bool TR = false;
bool LineGone = false;
bool bonkHasRan = false;
unsigned int lastTime = 0;
unsigned int turnTime = 0;
unsigned int lastLeft = 0;
unsigned int lastRight = 0;
int howLongTurn = 100;
int howLongReset = 200;
int turnSpeedLeft = -2000;
int turnSpeedRight = 4000;

public:

  // Function designed to navigate the turn
  pathFindingData pathFindingTurn(sensorStruct*);

  /** Function designed to do standard bending logic on a color,
  * Gets given current line color enum, a pointer to the sensorStruct,
  * an int which is what the last error for that color was.
  * and an int pointer which is an array of the lineSensorValues
  * which is read into, returns pathFindingData Struct.
  */
  pathFindingData pathFindingOnColor(lineColor, sensorStruct*, int, int*);

  /** Function that is used once brown line has been crossed to find the box,
  * and move it out of the circle and stop(return false) once it finishes.
  * Self contained loop as it is the end logic and stops program after
  * completion, gets given sensorStruct pointer, Pointer to motors,
  * lineSensorValues which is an int* which contains an array.
  */ 
  bool bonkthebox(sensorStruct*,Zumo32U4Motors*,int*);
};

#include "navigator.cpp"

#endif
