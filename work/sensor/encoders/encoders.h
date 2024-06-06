#ifndef ENCODERSS_H 
#define ENCODERSS_H

#include "../../headers.hpp"
#include <Arduino.h>

class CompatibleEncoders : public Zumo32U4Encoders, public Sensor
{
private:
    uint32_t EncoderValue[2];
public:
    CompatibleEncoders();
    uint32_t ReadLeft();
    uint32_t ReadRight();
    uint32_t* read();
    void ResetValues();
    void ReadOverSerial();

};

#include "encoders.cpp"

#endif
