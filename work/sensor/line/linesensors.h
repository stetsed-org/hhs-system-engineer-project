#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "../../headers.hpp"

class linesensors : public Zumo32U4LineSensors{
    public:
        linesensors();
        void readValues();
        void serialPrintValues();
        unsigned int* gibValues();

    private:
        //sensorReference Zumo32U4LineSensors; //ignore problem, for now... ;)
        Zumo32U4LineSensors lineSensorsLibrary; //renamed to clearly state the function comes from the library
        bool useEmitters;
        //int sensorAmount; //Currently not in use, might delete later if it remains unused
        unsigned int values[5];
        int pins[5];

};

#include "linesensors.cpp"

#endif
