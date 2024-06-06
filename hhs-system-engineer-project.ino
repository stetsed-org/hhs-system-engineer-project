#include <Arduino.h>
#include "work/serial/serial.cpp"
#include "work/headers.hpp"



#define RECHTS OCR1A
#define LINKS OCR1B

auto& xbee = Serial;

// Motors Setup
//Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
MotorController motorController;




// Initialize Navigator
navigator NavigatorInstance;


Zumo32U4ButtonB buttonB;

stateStorageStruct stateStorageStructObject;

// Algemene setup
void setup() {
  Wire.begin();

  void stop() {
    motors.setSpeeds(0, 0);
  }

  stateStorageStructObject.leftTurnActive = false;
  stateStorageStructObject.rightTurnActive = false;
};

void loop() {  
  //Serial1.println("Current Color State" + (String)stateStorageStructObject.currentColor);
 
  int blackCount = 0;
  int greenCount = 0;
  for(int i = 0; i < 5; ++i){
    //Serial1.print((String)i + " " + (String)stateStorageStructObject.currentColor[i] + " ");
      if (stateStorageStructObject.currentColor[i] == 'b'){
          blackCount += 1;
        }
      if (stateStorageStructObject.currentColor[i] == 'g'){
          greenCount += 1;
        }
    }
  //Serial1.println(" ");

  if (greenCount >= 2){
    pathFindingData temp = NavigatorInstance.pathFindingBlack(&sensorStructObject,lastError,lineSensorValues,200);
 
    lastError = temp.currentError;

    stateStorageStructObject.currentColor[4] = stateStorageStructObject.currentColor[3];
    stateStorageStructObject.currentColor[3] = stateStorageStructObject.currentColor[2];
    stateStorageStructObject.currentColor[2] = stateStorageStructObject.currentColor[1];
    stateStorageStructObject.currentColor[1] = stateStorageStructObject.currentColor[0];
    stateStorageStructObject.currentColor[0] = temp.currentColor;

    //Serial1.println(temp.rightMotorSpeed);
    temp.rightMotorSpeed = (int)abs(((float)temp.rightMotorSpeed * 1.03));

    //motors.setSpeeds(temp.leftMotorSpeed,temp.rightMotorSpeed);

  if (OCR1B < temp.leftMotorSpeed && OCR1B <= 350){
      OCR1B += 25;
    }
  if (OCR1A < temp.rightMotorSpeed && OCR1A <= 350){
      OCR1A += 25;
    }
  if (OCR1B > temp.leftMotorSpeed && OCR1B >= 25){
      OCR1B -= 25;
    }
  if (OCR1A > temp.rightMotorSpeed && OCR1A >= 25){
      OCR1A -= 25;
    }
 }

  else{
    pathFindingData temp = NavigatorInstance.pathFindingBlack(&sensorStructObject,lastError,lineSensorValues,350);
    
    lastError = temp.currentError;

    stateStorageStructObject.currentColor[4] = stateStorageStructObject.currentColor[3];
    stateStorageStructObject.currentColor[3] = stateStorageStructObject.currentColor[2];
    stateStorageStructObject.currentColor[2] = stateStorageStructObject.currentColor[1];
    stateStorageStructObject.currentColor[1] = stateStorageStructObject.currentColor[0];
    stateStorageStructObject.currentColor[0] = temp.currentColor;
    //Serial1.println(temp.rightMotorSpeed);
    temp.rightMotorSpeed = (int)abs(((float)temp.rightMotorSpeed * 1.03));

    //motors.setSpeeds(temp.leftMotorSpeed,temp.rightMotorSpeed);

  if (OCR1B < temp.leftMotorSpeed && OCR1B <= 350){
      OCR1B += 25;
    }
  if (OCR1A < temp.rightMotorSpeed && OCR1A <= 350){
      OCR1A += 25;
    }
  if (OCR1B > temp.leftMotorSpeed && OCR1B >= 25){
      OCR1B -= 25;
    }
  if (OCR1A > temp.rightMotorSpeed && OCR1A >= 25){
      OCR1A -= 25;
    }

  }
  //float output = calibrateMotor(motors,350,encodersObject);
  //Serial1.println(output,30);

  motorController.setSpeed(temp.leftMotorSpeed,temp.rightMotorSpeed);
  //float output = calibrateMotor(motors,350,encodersObject);
  //Serial1.println(output,30);

  //MotorController Testen
  if (Serial1.available() > 0) { //'> 0' is hier niet nodig, maar wordt gezien als een "best practice".
    char input = Serial.read();

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
  if (buttonA.isPressed())
  {
    motorController.stop();
    Serial1.println("Gestop met buttonA");
  }
  
}

void calibrateSensors()
{

  // Wait 1 second and then begin automatice not ignored as it ought to be sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motorController.setSpeed(-200, 200);
    }
    else
    {
      motorController.setSpeed(200, -200);
    }

    sensorStructObject.lineSensorPointer -> calibrate();
  }
  motorController.stop();
}