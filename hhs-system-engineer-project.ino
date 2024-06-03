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

// Initialize Navigator
navigator NavigatorInstance;

// Algemene setup
void setup() {
  Wire.begin();

  Serial1.begin(57600);
  Serial1.println("Zumo Active, Serial1 Output");
  proxzumo.initFrontSensor();
  proximitySensorObject = proxSensor(&proxzumo);

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


};

void loop() {  

  pathFindingData temp = NavigatorInstance.pathFindingBlack(&sensorStructObject,lastError,lineSensorValues);

  lastError = temp.currentError;

  Serial1.println(temp.rightMotorSpeed);
  temp.rightMotorSpeed = (int)abs(((float)temp.rightMotorSpeed * 1.03));

  motors.setSpeeds(temp.leftMotorSpeed,temp.rightMotorSpeed);
  //float output = calibrateMotor(motors,350,encodersObject);
  //Serial1.println(output,30);
}

void calibrateSensors()
{

  // Wait 1 second and then begin automatic sensor calibration
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
