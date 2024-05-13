#include "../../headers.hpp"
#include "encoders.h"


CompatibleEncoders::CompatibleEncoders(){
}

uint32_t CompatibleEncoders::ReadLeft(){
    EncoderValue[1] += getCountsAndResetLeft();
    return EncoderValue[1];
}

uint32_t CompatibleEncoders::ReadRight(){
    EncoderValue[2] += getCountsAndResetRight();
    return EncoderValue[2];
}

uint32_t CompatibleEncoders::Read(){
    return (EncoderValue[1],EncoderValue[2]);
}