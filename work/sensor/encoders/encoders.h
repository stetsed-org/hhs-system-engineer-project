#include "../../headers.hpp"
#include <string.h>

class CompatibleEncoders : public Zumo32U4Encoders
{
private:
    int32_t EncoderValue[2];
public:
    CompatibleEncoders();
    int32_t ReadLeft();
    int32_t ReadRight();
    int32_t Read();
    void ResetValues();
    void ReadOverSerial();

};
