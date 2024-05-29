bool debug = true;

#include <Arduino.h>
#include <stdarg.h>
#include "work/headers.hpp"


#define NUM_SENSORS 5

unsigned int lineSensorValues[NUM_SENSORS];

uint8_t selectedSensorIndex = 0;

int test = 0;
int speed = 0;

int count = 0;

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



// Algemene setup
void setup() {
  Wire.begin();

  Serial1.begin(4800);
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

  // Store the sensor Struct
  sensorStructObject.proximitySensorPointer = &proximitySensorObject;
  sensorStructObject.encodersPointer = &encodersObject;
  sensorStructObject.lineSensorPointer = &lineSensorObject;
  // sensorStructObject.gyroscopePointer = &gyroscopeObject;
  // sensorStructObject.magnetometerPointer = &magnetometerObject;
  // sensorStructObject.accelerometerPointer = &accelerometerObject;

  Serial.println();
}

void loop() {
    //if (calibratie){
    //  float calibratie = calibrateMotor(motors,200,encodersObject); 
    //  Serial1.println(calibratie);
    //  };
  };
