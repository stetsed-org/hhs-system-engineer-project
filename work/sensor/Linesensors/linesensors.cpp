#include "../../headers.hpp"
#include "linesensors.h"


/**
 * Constructor voor het maken van een object van linesensors. Tevens wordt hier useEmitters op true gezet. 
 * Deze kan als false worden ingesteld door de code aan te passen, mochten we de emitters toch niet willen gebruiken. 
 */
linesensors::linesensors():lineSensorsLibrary(),useEmitters(true){
  lineSensorsLibrary.initFiveSensors();
  //Serial1.println("linesensor object built"); // debug line, in comment geplaats wanneer deze niet gebruikt wordt
}

/**
 * Functie die zorgt dat via de methode van de library de values array die gevuld/overschreven wordt met de meest recente lijnsensor waardes.
 */
void linesensors::readValues(){
  lineSensorsLibrary.read(values, useEmitters);
}
/**
 * Functie die de values array returnt om deze buiten de klasse beschikbaar te stellen.
 */
unsigned int* linesensors::gibValues(){
  return values;
}

/**
 * Functie om de waardes uit de values array via de Xbee te printen.
 * De prints staan in een format dat overeenkomt met de instellingen van Robbert's dashboard,
 * hierdoor kan deze eventueel gebruikt worden om de waardes in een grafiek te kunnen bekijken ipv in de serial monitor.
 */
void linesensors::serialPrintValues(){
  Serial1.println("L"); // Duidt het begin van de reeks waardes aan, wordt tevens gebruikt door het dashboard om de waardes op de juiste manier in grafieken te tonen.
  Serial1.println(values[0]);
  Serial1.println(values[1]);
  Serial1.println(values[2]);
  Serial1.println(values[3]);
  Serial1.println(values[4]);
  Serial1.println("l"); // Duidt het einde van de reeds waardes aan, wordt tevens gebruikt door het dashboard om de waardes op de juiste manier in grafieken te tonen.
}