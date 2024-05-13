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
    return *EncoderValue;
}