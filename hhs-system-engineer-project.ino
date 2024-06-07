bool debug = 1;

#include "work/headers.hpp"
#include "work/ran-func.cpp"
#include "work/serial/serial.cpp"
#include "work/sensor/compass/accelerometer/accel.h"
#include "work/sensor/compass/gyroscope/gyro.h"
#include "work/sensor/compass/magnetometer/magnet.h"

int test = 0;
int speed = 0;

Accelerometer* accel;
Gyroscope* gyro;
Magnetometer* magnet;

Vector3 accelData;
Vector3 gyroData;
Vector3 magnetData;

char imuOutBuffer[139];

#define RECHTS OCR1A
#define LINKS OCR1B


// Sensors Declare
Zumo32U4ProximitySensors proxzumo;
Zumo32U4IMU imuzumo;
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
  Accelerometer accelerometerObject(&imuzumo);
  Gyroscope gyroscopeObject(&imuzumo);
  Magnetometer magnetometerObject(&imuzumo);


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
  sensorStructObject.gyroscopePointer = &gyroscopeObject;
  sensorStructObject.magnetometerPointer = &magnetometerObject;
  sensorStructObject.accelerometerPointer = &accelerometerObject;

  Serial.println();

  // check if compass can be initialized properly
  Zumo32U4IMU* compassInterfacePTR = new Zumo32U4IMU();
  if (compassInterfacePTR->init()){
    Serial1.println("Compass interface initialized successfully!");
    compassInterfacePTR->enableDefault();
    *accel = Accelerometer(compassInterfacePTR);
    *gyro = Gyroscope(compassInterfacePTR);
    *magnet =  Magnetometer(compassInterfacePTR);
    if (debug) {
      accel->PrintDebugInfo();
      gyro->PrintDebugInfo();
      magnet->PrintDebugInfo();
    }
  } else {
    Serial1.println("Compass interface probably not initialized successfully?");
  }
  // end of compass initialization test
}

void loop() {
    //if (calibratie){
    //  float calibratie = calibrateMotor(motors,200,encodersObject); 
    //  Serial1.println(calibratie);
    //  };

};
