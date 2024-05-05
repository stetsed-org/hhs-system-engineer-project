#include <Arduino.h>
#include "work/serial/serial.cpp"
#include "work/headers.hpp"



#define RECHTS OCR1A
#define LINKS OCR1B

auto& xbee = Serial;


Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;

//Motor Control class, m.b.v. ChatGPT. Zie bijlage B.2
//Aanpassingen: Schrappen van variabele 'int speed' en introductie van de variabelen 'int leftSpeed' en 'int rightSpeed'.
class MotorController {
  private:
    int leftSpeed;
    int rightSpeed;

  public:
    MotorController() {
      leftSpeed = 0;
      rightSpeed = 0;
    }
    //Methods voor het besturen van de motor/servos.
    //De methode moveForward is hier overbodig maar heb ik laten staan zitten zodat de knop ben keyboard besturing somewhat gescheiden is.
    void moveForward(int leftSpeed, int rightSpeed) {
      motors.setSpeeds(leftSpeed, rightSpeed);
    }
    void setSpeed(int leftSpeed, int rightSpeed) {
      motors.setSpeeds(leftSpeed, rightSpeed);
    }

    void stop() {
      motors.setSpeeds(0, 0);
    }
};



MotorController motorController;






void setup() {
  Serial1.begin(4800);
  Serial1.println("Zumo Active, Serial1 Output");

  xbee.begin(4800);
  
  // pinMode(A10, OUTPUT);
  // pinMode(A9, OUTPUT);
  // pinMode(16, OUTPUT);
  // pinMode(15, OUTPUT);
  // digitalWrite(16, LOW);
  // digitalWrite(15, LOW);
  // SetupTimer1();

  Serial.println();
}

void loop() {
   
  //Vraag hoe de Zumo met de xbee te besturen. Moet serial monitor kunnen gebruiken. 'Serial1'?
  //Kan nu alleen met usb serial monitor gebruiken en daarin de Zumo besturen.

  //if(Serial1.available()){
  //  readserial(leftSpeed, rightSpeed);
  //}


  //Check for keyboard input
  if (Serial.available() > 0) { //'> 0' is hier niet nodig, maar wordt gezien als een "best practice".
    char input = Serial.read();

    //Besturen met toetsenbord input, m.b.v ChatGPT. Zie bijlage B.1 en B.2
    //Aanpassingen: de snelheden, vertaling v.d. println outputs en het schrappen van overbodige comments.
    //Switch/Case: Leest input vanuit Serial Monitor executeerd een 'case' wat matched met de input.
      //Er moet vastwel een andere manier zijn om de Zumo met toetsenbord te besturen in C++.
      //Ik weet van een manier in Unity(C#) met gebruik van 'input.GetKeyDown' maar die manier werkt/bestaat niet in C++.
    switch (input) {
      case 'w':
        motorController.setSpeed(200, 200);
        Serial.println("Vooruit");
        break;
      case 's':
        motorController.setSpeed(-200, -200);
        Serial.println("Achteruit");
        break;
      case 'a':
        motorController.setSpeed(200, -200);
        Serial.println("Naar Links");
        break;
      case 'd':
        motorController.setSpeed(-200, 200);
        Serial.println("Naar Rechts");
        break;
      default:
        motorController.stop(); //If any key other 'w','a','s' or 'd' is received as input: Stop.
        Serial.println("Gestopt");
        break;
    }
  }
  
 //Deze heb ik niet weggehaald zodat de Zumo nog handmatig bestuurd kan worden.
 //Besturen van de Zumo met de onboard buttons, m.b.v ChatGPT. Zie bijlage B.2
 //Aanpassingen: println outputs en snelheden. Het gebruik van de .moveForward method heb ik behouden om twee manieren van bewsturen gescheiden te houden.
 
  if (buttonA.isPressed()) {
    motorController.moveForward(200, 200);
    Serial.println("Vooruit");
  } 
 
  else if (buttonB.isPressed()) {
    motorController.stop();
    Serial.println("Gestopt");
}


}

