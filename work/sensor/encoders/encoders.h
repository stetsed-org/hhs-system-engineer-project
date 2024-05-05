
class Encoder
{
    public:
        Encoder(bool);
        int ReadValue();
        void ResetEncoder();
        void SetEncoder(int);
        void ValueAdd1(); 
        void ValueSub1();
        void ValueAddNumber(int);
        void ValueSubNumber(int);
        void LEFTEncoderLogic();
        void RIGHTEncoderLogic();
    private:
        int _EncoderValue;
        bool _PrevValueA;
        bool _PrevValueB;
        bool _ValueA;
        bool _ValueB;
};