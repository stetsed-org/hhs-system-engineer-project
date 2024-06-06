#include "../../headers.hpp"
#include "linesensors.h"


//Constructor of linesensor class, configuring a few settings for correct use within the object.
linesensors::linesensors():lineSensorsLibrary(),useEmitters(true){
  
  lineSensorsLibrary.initFiveSensors();
  Serial1.println("linesensor object built"); 
}

//Function to read the value of each linesensor, mainly to use within this class.
void linesensors::readValues(){
  lineSensorsLibrary.read(values, useEmitters);
}

//Function to print the value of each linesensor in a format used by the dashboard.
void linesensors::serialPrintValues(){
  Serial1.println("L"); // Begin of linesensor measurement values
  Serial1.println(values[0]);
  Serial1.println(values[1]);
  Serial1.println(values[2]);
  Serial1.println(values[3]);
  Serial1.println(values[4]);
  Serial1.println("l"); // end of these measurement values. These are mainly important for use in the dashboard, to correctly insert the values.
}

unsigned int* linesensors::read(){
  return values;
}



int linesensors::readLine_but_good_and_not_colour_blind(unsigned int *sensor_values,
    unsigned char readMode, unsigned char white_line)
{
    unsigned char i, on_line= 0;
    unsigned long avg; // this is for the weighted total, which is long
                       // before division
    unsigned int sum; // this is for the denominator which is <= 64000

    readCalibrated(sensor_values, readMode);

    avg = 0;
    sum = 0;

    for(i=0;i<_numSensors;i++) {
        int value = sensor_values[i];
        if(white_line)
            value = 1000-value;

        // keep track of whether we see the line at all
        if(value > 170) {
            on_line = 1;
        }


        // only average in values that are above a noise threshold
        if(value > 50) {
            avg += (long)(value) * (i * 1000);
            sum += value;
        }
    }

    if(!on_line)
    {
        // If it last read to the left of center, return 0.
        if(_lastValue < (_numSensors-1)*1000/2)
            return 0;

        // If it last read to the right of center, return the max.
        else
            return (_numSensors-1)*1000;

    }

    _lastValue = avg/sum;

    return _lastValue;
}



