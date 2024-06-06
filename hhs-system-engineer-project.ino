//Deze is alleen bedoeld om de MotorController te testen. Dit gaat niet in de main.

#include <Arduino.h>
#include "work/serial/serial.cpp"
#include "work/headers.hpp"
#include "work/motor/MotorController.h"



#define RECHTS OCR1A
#define LINKS OCR1B

auto& xbee = Serial;


//Motors Setup
MotorController motorController;
Zumo32U4ButtonA buttonA;







void setup() {
  Serial1.begin(57600);
  Serial1.println("Zumo Active, Serial1 Output");

  //xbee.begin(57600);

  Serial1.println();
}

void loop() {
   

  

}

