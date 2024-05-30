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

unsigned int* linesensors::gibValues(){
  return values;
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