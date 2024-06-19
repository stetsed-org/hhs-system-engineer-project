bool debug = false;

#include <Arduino.h>
#include <stdarg.h>
#include "work/headers.hpp"

unsigned int lineSensorValues[5];

uint8_t selectedSensorIndex = 0;

float MotorCorrectionFactor = 1.04;
int lastErrorBlack = 0;
int lastErrorGreen =0;

char imuOutBuffer[139];

int readyLeft = false; //new
int readyRight = false; //new

bool readyLeftForReal = false;
bool readyRightForReal = false;

long rightDetectTime = 0;
long leftDetectTime = 0;

bool Finished = false;

#define RECHTS OCR1A
#define LINKS OCR1B

// Sensors Declare
Zumo32U4ProximitySensors proxzumo;
proxSensor proximitySensorObject;
CompatibleEncoders encodersObject;
linesensors lineSensorObject;
sensorStruct sensorStructObject;

SerialJSON* xbee = new SerialJSON;

// Motors Setup
Zumo32U4Motors motors;
MotorController motorController;

// Initialize Navigator
navigator NavigatorInstance;

stateStorageStruct stateStorageStructObject;

Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

void setup() {
  delay(10000); 
  // Algemene setup
  Wire.begin();
  Serial1.begin(57600);
  
  proxzumo.initFrontSensor();
  proximitySensorObject = proxSensor(&proxzumo);

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

  calibrateSensors(); 

  stateStorageStructObject.leftTurnActive = false;
  stateStorageStructObject.rightTurnActive = false;
};

void loop() {
  // Allow for restarting/starting the program with buttonA including recalibration.
  if (buttonA.getSingleDebouncedPress()){
    Finished = !Finished;
    calibrateSensors();
    delay(5000);
  }
  while (!Finished){
  if (buttonA.getSingleDebouncedPress()){
    Finished = !Finished;
  }
  int blackCount = 0;
  int greenCount = 0;
  int brownCount = 0;
  // Count the current amount of a specific color in the array
  for(int i = 0; i < 10; ++i){
      if (stateStorageStructObject.currentColor[i] == 'b'){
          blackCount++;
        }
      if (stateStorageStructObject.currentColor[i] == 'g'){
          greenCount ++;
        }
      if (stateStorageStructObject.currentColor[i] == 'r'){
          brownCount++;
      }
    }
  pathFindingData temp;

  // Run the logic as decided by what the count is of that color to avoid flip-flop condition
  if (greenCount >= 8 && brownCount < 4){
    temp = NavigatorInstance.pathFindingOnColor(lineColor::Green, &sensorStructObject,lastErrorGreen,lineSensorValues, xbee);
 
    lastErrorGreen = temp.currentError;
  }
  // else if (brownCount >= 4){
  //   NavigatorInstance.bonkthebox(&sensorStructObject,&motors,lineSensorValues);
  //   Finished = true;
  //   break;
  // }
  else{
    temp = NavigatorInstance.pathFindingOnColor(lineColor::Black, &sensorStructObject,lastErrorBlack,lineSensorValues, xbee);
    
    lastErrorBlack = temp.currentError;
  }


  // Assuming color isn't n which means can't decide it will move the array up by 1 and add the new to the start
  if (!(temp.currentColor == 'n')) {
    for (short i=9; i>0; i--) {
    stateStorageStructObject.currentColor[i] = stateStorageStructObject.currentColor[i-1];
    }
    stateStorageStructObject.currentColor[0] = temp.currentColor;
  }

  //turnGrayLogic();
 
  // Add the Correction factor to avoid drift.
  //temp.rightMotorSpeed = (int)((float)temp.rightMotorSpeed * MotorCorrectionFactor);

  //motors.setSpeeds(temp.leftMotorSpeed,temp.rightMotorSpeed);
  //xbee -> sendJSON();

  Serial1.println(lineSensorValues[2]);
  }
}

void calibrateSensors()
{

  // Wait 1 second and then begin automatice not ignored as it ought to be sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for(uint16_t i = 0; i < 200; i++)
  {
    if (i > 50 && i <= 150)
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

// Function to detect and turn when a gray line is detected on right or left
void turnGrayLogic(){
  // Check if we see 5 consecutive gray measurments on the left and then we know we need to make a left turn.
  if ((lineSensorValues[0] < 320) && (160 < lineSensorValues[0])){
    readyLeft++;
    if (readyLeft >= 5){
      readyLeftForReal = true;
      leftDetectTime = millis();
    }
  }
  else readyLeft = 0;
  // Check if we see 5 consecutive gray measurments on the right and then we know we need to make a right turn.
  if ((lineSensorValues[4] < 320) && (160 < lineSensorValues[4])){
    readyRight++;
    if (readyRight >= 5){
      readyRightForReal = true;
      rightDetectTime = millis();
    }
  }
  else readyRight = 0;

  // If we have the turn verified and the left detects a black line we turn hard left and then reset.
  if ( readyLeftForReal && lineSensorValues[0]> 750){
    encodersObject.ResetValues();
    while(encodersObject.getCountsRight() < (910)){
      motors.setRightSpeed(350);
      motors.setLeftSpeed(-200);
    }
    readyLeft = false;
    readyLeftForReal = false;
    leftDetectTime = 0;
  }
  // If the turn detection was greater than 2 seconds ago we reset assuming it was an error.
  else if((millis()- leftDetectTime) >= 2000 && leftDetectTime != 0){
    leftDetectTime = 0;
    readyLeft = 0;
    readyLeftForReal = 0;
  }
  // If we have the turn verified and the right detects a black line we turn hard right and then reset.
  if (readyRightForReal && lineSensorValues[4]> 750){
    encodersObject.ResetValues();
    while(encodersObject.getCountsLeft() < (910)){
      motors.setLeftSpeed(350);
      motors.setRightSpeed(-200);
    }
    readyRight = false;
    readyRightForReal = false;
    rightDetectTime = 0;
  }
  // If the turn detection was greater than 2 seconds ago we reset assuming it was an error.
  else if((millis()- rightDetectTime) >= 2000 && rightDetectTime != 0){
    rightDetectTime = 0;
    readyRight = 0;
    readyRightForReal = 0;
  }
}
