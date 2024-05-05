#define __AVR_ATmega32U4__

#include "encoders.h"
#include <Arduino.h>
#include <FastGPIO.h>
#include <avr/interrupt.h>


#define LEFT_XOR   8
#define LEFT_B     IO_E2
#define RIGHT_XOR  7
#define RIGHT_B    23



Encoder::Encoder(bool EncoderisLeft):ValueA(0),ValueB(0),EncoderValue(0),PrevValueA(0),PrevValueB(0)
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
    return EncoderValue;
}


void Encoder::ResetEncoder()
{
    EncoderValue = 0;
}
void Encoder::SetEncoder(int Number)
{
    EncoderValue = Number;
}
void Encoder::ValueAdd1()
{
    EncoderValue++;
}
void Encoder::ValueSub1()
{
    EncoderValue--;
}
void Encoder::ValueAddNumber(int Number)
{
    EncoderValue += Number;
}
void Encoder::ValueSubNumber(int Number)
{
    EncoderValue -= Number;
}
void Encoder::LEFTEncoderLogic()
{  
    ValueB = FastGPIO::Pin<LEFT_B>::isInputHigh();
    ValueA = FastGPIO::Pin<LEFT_XOR>::isInputHigh() ^ ValueB;

    EncoderValue += (ValueA ^ PrevValueB) - (PrevValueA ^ ValueB);

    PrevValueA = ValueA;
    PrevValueB = ValueB;
}

void Encoder::RIGHTEncoderLogic()
{  
    ValueB = FastGPIO::Pin<RIGHT_B>::isInputHigh();
    ValueA = FastGPIO::Pin<RIGHT_XOR>::isInputHigh() ^ ValueB;

    EncoderValue += (ValueA ^ PrevValueB) - (PrevValueA ^ ValueB);

    PrevValueA = ValueA;
    PrevValueB = ValueB;
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


ISR(PCINT0vect)
{   
    EncoderLeft.LEFTEncoderLogic();
}

ISR(INT6vect)
{
    EncoderRight.RIGHTEncoderLogic();
}