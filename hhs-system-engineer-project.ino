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
  Serial1.begin(4800);
  Serial1.println("Zumo Active, Serial1 Output");

  xbee.begin(4800);

  Serial1.println();
}

void loop() {
   

  //MotorController Test
  if (Serial1.available() > 0) {
    char input = Serial1.read();

    //Besturen met toetsenbord input, m.b.v ChatGPT. Zie bijlage B.1 en B.2
    //Aanpassingen: de snelheden, vertaling v.d. println outputs en het schrappen van overbodige comments.
    //Switch/Case: Leest input vanuit Serial Monitor executeerd een 'case' wat matched met de input.
    
    switch (input) {
      case 'w':
        motorController.setSpeed(200, 200);
        Serial1.println("Vooruit");
        break;
      case 's':
        motorController.setSpeed(-200, -200);
        Serial1.println("Achteruit");
        break;
      case 'a':
        motorController.setSpeed(200, -200);
        Serial1.println("Naar Links");
        break;
      case 'd':
        motorController.setSpeed(-200, 200);
        Serial1.println("Naar Rechts");
        break;
      default:
        motorController.stop(); //If any key other 'w','a','s' or 'd' is received as input: Stop.
        Serial1.println("Gestopt");
        break;
    }
  }
 
  else if (buttonA.isPressed()) {
    motorController.stop();
    Serial1.println("Gestopt");
}


}

