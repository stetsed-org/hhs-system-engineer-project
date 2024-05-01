#include "../headers.hpp"

#define RECHTS OCR1A
#define LINKS OCR1B

void readserial(int test, int speed){    
test = Serial1.read();
    switch (test) {
      case 'm':
        speed = 400;
        LINKS = speed;
        RECHTS = speed;
        Serial1.println(speed);
        break;

      case 'k':
        speed = 0;
        LINKS = speed;
        RECHTS = speed;
        Serial1.println(speed);
        break;

      case '1':
        speed = 128;
        OCR1B = speed;
        RECHTS = speed;
        Serial1.println(speed);
        break;

      case '2':
        speed = 200;
        OCR1B = speed;
        RECHTS = speed;
        Serial1.println(speed);
        break;

      case 'a':
        digitalWrite(16, HIGH);
        digitalWrite(15, LOW);
        break;
      case 'd':
        digitalWrite(16, LOW);
        digitalWrite(15, HIGH);
        break;
      case 's':
        digitalWrite(16, HIGH);
        digitalWrite(15, HIGH);
        break;
      case 'w':
        digitalWrite(16, LOW);
        digitalWrite(15, LOW);
        break;


      default:
        speed = 0;
        LINKS = speed;
        RECHTS = speed;
        Serial1.println(speed);
        break;
    }
}
