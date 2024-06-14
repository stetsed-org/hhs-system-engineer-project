#ifndef _SERIALJSON_CPP_
#define _SERIALJSON_CPP_
#include "../headers.hpp"

    SerialJSON::SerialJSON() : JSONTotal("{"), firstValue(true){}
    SerialJSON::~SerialJSON(){}

    void SerialJSON::addNewData(String name, long number){
        if(!firstValue){
            JSONTotal += Spacer;
        }else firstValue = false;
        JSONTotal += '"' + name + '"' + ": " + number;
    }

    void SerialJSON::addNewData(String name, int* numbs, int amount){
        if(!firstValue){
            JSONTotal += Spacer;
        }else firstValue = false;
        JSONTotal += '"' + name + '"' + ": " + arrayStart;
        for (int i = 0; i < amount -1; i++){
            JSONTotal += numbs[i] + Spacer;
        }
        JSONTotal += numbs[amount];
        JSONTotal += arrayEnd;
    }

    void SerialJSON::sendJSON(){
        JSONTotal += JSONEnd;
        Serial1.println(JSONTotal);
        JSONTotal = "{";
        firstValue = true;
    }


#endif