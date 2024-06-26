#include <Arduino.h>


/** Setup the timers we need for the project which 
 * includes allowing us to make smaller steps in the motor
 * but keep the cycles in sync to avoid pull back.
*/
void SetupTimer1(){
  // TCCR1A contains: COM1A1, COM1A0, COM1B1, COM1B0, COM1C1, COM1C0, WGM11, WGM10
  // TCCR1B contains: ICNC1, ICES1, N/A, WGM13, WGM12, CS12, SC11, SC10
  // TIMSK1 contains: N/A, N/A, ICIE1, N/A, OCIE1C, OCIE1B, OCIE1A, TOIE1

  TCCR1A = 0b10100010;
  TCCR1B = 0b00011001;
  ICR1 = 400;
  OCR1A = 0;
  OCR1B = 0;
}
