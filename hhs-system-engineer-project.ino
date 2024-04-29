#include "work/headers.hpp"
#include "work/ran-func.cpp"
#include "work/serial/serial.cpp"
#include "work/sensor/compass/accelerometer/accel.h"
#include "work/sensor/compass/gyroscope/gyro.h"
#include "work/sensor/compass/magnetometer/magnet.h"

int test = 0;
int speed = 0;

Accelerometer accel;
Gyroscope gyro;
Magnetometer magnet;

Vector3 accelData;
Vector3 gyroData;
Vector3 magnetData;

#define RECHTS OCR1A
#define LINKS OCR1B

//auto& xbee = Serial;

void setup() {
  Serial1.begin(4800);
  Serial1.println("Zumo Active, Serial1 Output");

  // xbee.begin(4800);
  
  pinMode(A10, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(16, LOW);
  digitalWrite(15, LOW);
  SetupTimer1();

  Serial.println();

  CompassBase* cBase = new CompassBase();
  cBase->Initialize();
  delete cBase;

  accel = Accelerometer();
  gyro = Gyroscope();
  magnet = Magnetometer();

  accelData = accel.Values();
  gyroData = gyro.Values();
  magnetData = magnet.Values();
}

void loop() {
  //if(Serial1.available()){
    //readserial(test,speed);
  //}
  accelData = accel.Values();
  gyroData = gyro.Values();
  magnetData = magnet.Values();

  printCompassValues();
}

void printCompassValues() {
  Serial1.print("Acceleration:");
  Serial1.print("\r\nX: "); Serial1.print(accelData.x);
  Serial1.print("\r\nY: "); Serial1.print(accelData.y);
  Serial1.print("\r\nZ: "); Serial1.print(accelData.z);

  Serial1.print("\r\nGyroscope:");
  Serial1.print("\r\nX: "); Serial1.print(gyroData.x);
  Serial1.print("\r\nY: "); Serial1.print(gyroData.y);
  Serial1.print("\r\nZ: "); Serial1.print(gyroData.z);

  Serial1.print("\r\nMagnetometer:");
  Serial1.print("\r\nX: "); Serial1.print(magnetData.x);
  Serial1.print("\r\nY: "); Serial1.print(magnetData.y);
  Serial1.print("\r\nZ: "); Serial1.print(magnetData.z);
  Serial1.println("----------------");
}
