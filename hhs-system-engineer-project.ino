#include <Arduino.h>
#include "work/ran-func.cpp"
#include "work/serial/serial.cpp"

Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;

#define NUM_SENSORS 5

unsigned int lineSensorValues[NUM_SENSORS];

bool useEmitters = true;

uint8_t selectedSensorIndex = 0;

int test = 0;
int speed = 0;

#define RECHTS OCR1A
#define LINKS OCR1B

auto& xbee = Serial;

// Algemene setup
void setup() {
  Serial1.begin(4800);
  Serial1.println("Zumo Active, Serial1 Output");

  xbee.begin(4800);
  
  pinMode(A10, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(16, LOW);
  digitalWrite(15, LOW);
  SetupTimer1();

  Serial.println();

  // Methode wordt aangeroepen om alle 5 de sensoren te gebruiken (3 kan ook, maar dat doen wij niet).
  lineSensors.initFiveSensors();
}

// Methode die aangeroepen wordt. Hierin wordt beschreven dat de gelezen waardes van de sensoren op 1 lijn met tussenruimte moeten worden geprint naar serial.
void printReadingsToSerial()
{
  char buffer[80];
  sprintf(buffer, "%4d %4d %4d %4d %4d %c\n",
    lineSensorValues[0],
    lineSensorValues[1],
    lineSensorValues[2],
    lineSensorValues[3],
    lineSensorValues[4],
    useEmitters ? 'E' : 'e'
  );
  Serial1.print(buffer);
}

void loop() {
  if(Serial1.available()){ // Serial1 error kan genegeerd worden, deze werkt wel met de Arduino IDE
    readserial(test,speed);
  }
  static uint16_t lastSampleTime = 0;

  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();

    // Leest alle sensorwaardes uit van de lijnsensoren. Ook wordt via de variable useEmitters aangegeven of de IR emitters gebruikt moeten worden.
    lineSensors.read(lineSensorValues, useEmitters);

    // Stuurt de gelezen waardes naar de serial (te zien in de "serial monitor" in Visual Studio).
    printReadingsToSerial();
  }
}
// Code kan gerunt worden in Visual Studio door in de bovenste balk ">arduino: verify" of ">arduino: upload" in te voeren