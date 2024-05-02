#define __AVR_ATmega32U4__
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

char imuOutBuffer[139];

#define RECHTS OCR1A
#define LINKS OCR1B

//auto& xbee = Serial;

void setup() {
  Wire.begin();

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

  // check if compass can be initialized properly
  Zumo32U4IMU* compassInterfacePTR = new Zumo32U4IMU();
  if (compassInterfacePTR->init())
	{
		Serial1.println("Compass interface initialized successfully!");
    compassInterfacePTR->enableDefault();
    accel = Accelerometer(compassInterfacePTR);
    gyro = Gyroscope(compassInterfacePTR);
    magnet =  Magnetometer(compassInterfacePTR);

    // these three are not implemented yet
    // accel.PrintDebugInfo();
    // gyro.PrintDebugInfo();
    // magnet.PrintDebugInfo();
	} else {
		Serial1.println("Compass interface probably not initialized successfully?");
	}
  // end of compass initialization test

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
  Serial1.println(sprintf(imuOutBuffer, "%s\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s%d\r\n%s",
    "--------------------",
    "aX: ", accelData.x,
    "aY: ", accelData.y,
    "aZ: ", accelData.z,
    "gX: ", gyroData.x,
    "gY: ", gyroData.y,
    "gZ: ", gyroData.z,
    "mX: ", magnetData.x,
    "mY: ", magnetData.y,
    "mZ: ", magnetData.z,
    "--------------------"));
    
  Serial1.println(imuOutBuffer);
}