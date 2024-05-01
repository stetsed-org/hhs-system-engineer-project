bool debug = true;

int test = 0;
int speed = 0;

int count = 0;

#include <Arduino.h>
#include <stdarg.h>
#include "work/ran-func.cpp"
#include "work/serial/serial.cpp"
#include "work/sensor/proximity/proxsensor.h"

#define RECHTS OCR1A
#define LINKS OCR1B

auto& xbee = Serial;

// Proxmity Sensor Setup
Zumo32U4ProximitySensors proxzumo;
proxSensor proximity;

void setup() {
  Serial1.begin(4800);
  Serial1.println("Zumo Active, Serial1 Output");
  proxzumo.initFrontSensor();
  proximity = proxSensor(proxzumo);


  xbee.begin(4800);
  
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
  //if(Serial1.available()){
  //  readserial(test,speed);
  //}
}

