#include "../../headers.hpp"
#include "linesensors.h" //includes the linesensor file of the library

Zumo32U4LineSensors lineSensors;

bool useEmitters = true; // set the IR emitters to be used
unsigned int sensorValues[5]; // set the amount of sensors to 5 (according to the library, 3 can also be used)

/* The following function prints the current value of every linesensor to the serial monitor (in VSC).
Values are shown in one line. On the left is value 0, which is the most left sensor while looking at the ZUMO upright and pointing away from you.
Value 4 is the most right on the screen and is the most right sensor. */
void printReadingsToSerial()
{
  char buffer[80];
  sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
    sensorValues[0],
    sensorValues[1],
    sensorValues[2],
    sensorValues[3],
    sensorValues[4],
    useEmitters ? 'E' : 'e'
  );
  Serial1.print(buffer);
}

void setup(){
    lineSensors.initFiveSensors(); // set lineSensors to be using all 5 sensors (according to the library, 3 can also be used)
}

void loop(){
    printReadingsToSerial();
    delay(5000);
}

//-------------------------

