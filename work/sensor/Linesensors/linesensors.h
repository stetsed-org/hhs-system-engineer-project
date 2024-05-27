#include "../../headers.hpp"



class linesensors : public Zumo32U4LineSensors{
    public:
        linesensors();
        void readValues();
        void serialPrintValues();

    private:
        //sensorReference Zumo32U4LineSensors; //ignore problem, for now... ;)
        Zumo32U4LineSensors lineSensorsLibrary; //renamed to clearly state the function comes from the library
        bool useEmitters;
        //int sensorAmount; //Currently not in use, might delete later if it remains unused
        unsigned int values[5];
        int pins[5];
};