bool debug = true;

#include <Arduino.h>
#include <stdarg.h>
#include "work/headers.hpp"

unsigned int lineSensorValues[5];

uint8_t selectedSensorIndex = 0;

float MotorCorrectionFactor = 1.03;
int lastError = 0;

char imuOutBuffer[139];

#define RECHTS OCR1A
#define LINKS OCR1B

// Sensors Declare
Zumo32U4ProximitySensors proxzumo;
proxSensor proximitySensorObject;
CompatibleEncoders encodersObject;
linesensors lineSensorObject;
sensorStruct sensorStructObject;

// Motors Setup
Zumo32U4Motors motors;
MotorController motorController;

// Initialize Navigator
navigator NavigatorInstance;


Zumo32U4ButtonB buttonB;

void setup() {
  stateStorageStruct stateStorageStructObject;
  
  // Algemene setup
  Wire.begin();

  Serial1.begin(57600);
  Serial1.println("Zumo Active, Serial1 Output");
  proxzumo.initFrontSensor();
  proximitySensorObject = proxSensor(&proxzumo);

  //xbee.begin(57600);

  Serial1.println();
  
  // xbee.begin(4800);
  
  pinMode(A10, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(16, LOW);
  digitalWrite(15, LOW);
  SetupTimer1();
  
  // Note: We need to initialize, initializing from the constructor doesn't work?
  lineSensorObject.initFiveSensors();

  // Store the sensor Struct
  sensorStructObject.proximitySensorPointer = &proximitySensorObject;
  sensorStructObject.encodersPointer = &encodersObject;
  sensorStructObject.lineSensorPointer = &lineSensorObject;
  // sensorStructObject.gyroscopePointer = &gyroscopeObject;
  // sensorStructObject.magnetometerPointer = &magnetometerObject;
  // sensorStructObject.accelerometerPointer = &accelerometerObject; 

  Serial.println();

  calibrateSensors(); 

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
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    sensorStructObject.lineSensorPointer -> calibrate();
  }
  motors.setSpeeds(0, 0);
}
