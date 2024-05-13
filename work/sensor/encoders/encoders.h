#include "../../headers.hpp"

class CompatibleEncoders : public Zumo32U4Encoders
{
private:
    uint32_t EncoderValue[2];
public:
    CompatibleEncoders();
    uint32_t ReadLeft();
    uint32_t ReadRight();
    uint32_t Read();
};
