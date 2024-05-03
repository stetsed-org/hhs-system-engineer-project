#include <Arduino.h>
#include "work/serial/serial.cpp"
#include "work/headers.hpp"



#define RECHTS OCR1A
#define LINKS OCR1B

auto& xbee = Serial;


Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;

//Motor Control class
class MotorController {
  private:
    int leftSpeed;
    int rightSpeed;

  public:
    MotorController() {
      leftSpeed = 0;
      rightSpeed = 0;
    }

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
   
  //Vraag hoe de Zumo met de xbee te besturen. Moet serial monitor kunnen gebruiken.
  //Kan nu alleen met usb serial monitor gebruiken en daarin de Zumo besturen.

  //if(Serial1.available()){
  //  readserial(leftSpeed, rightSpeed);
  //}


  //Check for keyboard input
  if (Serial.available() > 0) {
    char input = Serial.read();

    //Movement based off of keyboard input. 
    //Switch/Case: Reads input in serial monitor and a a case is executed based off of that input.
      //Er moet vastwel een andere manier zijn om de Zumo met toetsenbord te besturen in C++.
      //Ik weet van een manier in Unity(C#).
    switch (input) {
      case 'w':
        motorController.setSpeed(100, 100); //moveForward
        Serial.println("Vooruit");
        break;
      case 's':
        motorController.setSpeed(-100, -100); //moveBackward
        Serial.println("Achteruit");
        break;
      case 'a':
        motorController.setSpeed(200, -200); //turnLeft
        Serial.println("Naar Links");
        break;
      case 'd':
        motorController.setSpeed(-200, 200); //turnRight
        Serial.println("Naar Rechts");
        break;
      default:
        motorController.stop(); //When any key other than 'w','a','s' or 'd' is received as input: Stop.
        Serial.println("Stopped");
        break;
    }
  }
  
//Manipulation of the Zumo using the onboard buttons.
 //On buttonA press, moveForward
  if (buttonA.isPressed()) {
    motorController.moveForward(100, 100);
    Serial.println("Vooruit");
  } 
  //On buttonB press, stop
  else if (buttonB.isPressed()) {
    motorController.stop();
    Serial.println("Stopped");
}


}

