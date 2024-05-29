linesensors uwu;
#define NUM_SENSORS 5

unsigned int lineSensorValues[NUM_SENSORS];

uint8_t selectedSensorIndex = 0;

bool debug = true;

int test = 0;
int speed = 0;

int count = 0;

bool calibratie = true;

#include <Arduino.h>
#include <stdarg.h>
#include "work/headers.hpp"

Accelerometer* accel;
Gyroscope* gyro;
Magnetometer* magnet;

Vector3 accelData;
Vector3 gyroData;
Vector3 magnetData;

char imuOutBuffer[139];

#define RECHTS OCR1A
#define LINKS OCR1B

//auto& xbee = Serial;

// Proxmity Sensor Setup
Zumo32U4ProximitySensors proxzumo;
proxSensor proximity;

Zumo32U4Motors motors;
CompatibleEncoders encoders;



// Algemene setup
void setup() {
  Wire.begin();

  Serial1.begin(4800);
  Serial1.println("Zumo Active, Serial1 Output");
  proxzumo.initFrontSensor();
  proximity = proxSensor(&proxzumo);


  // xbee.begin(4800);
  
  pinMode(A10, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(16, LOW);
  digitalWrite(15, LOW);
  SetupTimer1();

  Serial.println();
}

void loop() {
    if (calibratie){
      float calibratie = calibrateMotor(motors,200,encoders); 
      Serial1.println(calibratie);
      };
  };
