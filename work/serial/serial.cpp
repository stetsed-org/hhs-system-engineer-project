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
        break;

      case 'k':
        speed = 0;
        LINKS = speed;
        RECHTS = speed;
        break;

      case '1':
        speed = 128;
        OCR1B = speed;
        RECHTS = speed;
        break;

      case '2':
        speed = 200;
        OCR1B = speed;
        RECHTS = speed;
        break;

      default:
        speed = 0;
        LINKS = speed;
        RECHTS = speed;
        break;
    }
}
