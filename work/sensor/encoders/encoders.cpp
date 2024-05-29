#include "../../headers.hpp"
#include "encoders.h"


CompatibleEncoders::CompatibleEncoders(){
}

uint32_t CompatibleEncoders::ReadLeft(){
    EncoderValue[0] += getCountsAndResetLeft();
    return EncoderValue[0];
}

uint32_t CompatibleEncoders::ReadRight(){
    EncoderValue[1] += getCountsAndResetRight();
    return EncoderValue[1];
}

uint32_t CompatibleEncoders::Read(){
    EncoderValue[0] += getCountsAndResetLeft();
    EncoderValue[1] += getCountsAndResetRight();
    return *EncoderValue;
}

void CompatibleEncoders::ReadOverSerial(){
    EncoderValue[0] += getCountsAndResetLeft();
    EncoderValue[1] += getCountsAndResetRight();
    Serial1.println("E");
    Serial1.println(EncoderValue[0]);
    Serial1.println(EncoderValue[1]);
    Serial1.println("e");
}

void CompatibleEncoders::ResetValues(){
    getCountsAndResetLeft();
    getCountsAndResetRight();
    EncoderValue[0] = 0;
    EncoderValue[1] = 0;
}
