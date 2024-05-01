#define __AVR_ATmega32U4__

#include "encoders.h"
#include <Arduino.h>
#include <FastGPIO.h>
#include <avr/interrupt.h>


#define LEFT_XOR   8
#define LEFT_B     IO_E2
#define RIGHT_XOR  7
#define RIGHT_B    23



Encoder::Encoder(bool EncoderisLeft):_ValueA(0),_ValueB(0),_EncoderValue(0),_PrevValueA(0),_PrevValueB(0)
{
    if (EncoderisLeft)
    {
        FastGPIO::Pin<LEFT_XOR>::setInputPulledUp();
        FastGPIO::Pin<LEFT_B>::setInputPulledUp();
    }
    else
    {
        FastGPIO::Pin<RIGHT_XOR>::setInputPulledUp();
        FastGPIO::Pin<RIGHT_B>::setInputPulledUp();
    }
}

int Encoder::ReadValue()
{
    return _EncoderValue;
}


void Encoder::ResetEncoder()
{
    _EncoderValue = 0;
}
void Encoder::SetEncoder(int Number)
{
    _EncoderValue = Number;
}
void Encoder::ValueAdd1()
{
    _EncoderValue++;
}
void Encoder::ValueSub1()
{
    _EncoderValue--;
}
void Encoder::ValueAddNumber(int Number)
{
    _EncoderValue += Number;
}
void Encoder::ValueSubNumber(int Number)
{
    _EncoderValue -= Number;
}
void Encoder::LEFTEncoderLogic()
{  
    _ValueB = FastGPIO::Pin<LEFT_B>::isInputHigh();
    _ValueA = FastGPIO::Pin<LEFT_XOR>::isInputHigh() ^ _ValueB;

    _EncoderValue += (_ValueA ^ _PrevValueB) - (_PrevValueA ^ _ValueB);

    _PrevValueA = _ValueA;
    _PrevValueB = _ValueB;
}

void Encoder::RIGHTEncoderLogic()
{  
    _ValueB = FastGPIO::Pin<RIGHT_B>::isInputHigh();
    _ValueA = FastGPIO::Pin<RIGHT_XOR>::isInputHigh() ^ _ValueB;

    _EncoderValue += (_ValueA ^ _PrevValueB) - (_PrevValueA ^ _ValueB);

    _PrevValueA = _ValueA;
    _PrevValueB = _ValueB;
}

void EncoderInit()
{
    PCICR = (1 << PCIE0);
    PCMSK0 = (1 << PCINT4);
    PCIFR = (1 << PCIF0); 

    EICRB |= (0<<ISC61) || (1<<ISC60);
    EIMSK |= (0<<INT6); 

    sei();
}
Encoder EncoderLeft(true);
Encoder EncoderRight(false);


ISR(PCINT0_vect)
{   
    EncoderLeft.LEFTEncoderLogic();
}

ISR(INT6_vect)
{
    EncoderRight.RIGHTEncoderLogic();
}