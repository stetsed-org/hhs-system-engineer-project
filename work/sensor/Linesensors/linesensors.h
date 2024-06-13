#include "../../headers.hpp"


/**
 * De linesensors klasse zorgt ervoor dat met behulp van de Zumo library de 5 lijnsensoren aan de voorkant van de Zumo kunnen worden uitgelezen.
 * De uitgelezen waardes kunnen daarna opgevraagt of direct over de Xbee geprint worden door middel van de publieke functies.
 */
class linesensors : public Zumo32U4LineSensors{
    public:
        linesensors(); // Constructor
        void readValues(); // Leest alle lijnsensoren uit en slaat de waardes op in de values array.
        void serialPrintValues(); // Print de waardes uit de values array in een vorm die bruikbaar is met Robbert's dashboard voor het eventueel debuggen/calibreren.
        unsigned int* gibValues(); // returnd de values array voor het gebruik elders buiten de klasse.

    private:
        Zumo32U4LineSensors lineSensorsLibrary; //Object van de library voor het gebruik van functies uit deze library.
        bool useEmitters; // Bool die gebruikt kan worden om de IR emitters aan of uit te zetten. Deze dient alleen als instelling en er is geen functie om deze aan te passen.
        unsigned int values[5]; // array die de meest recente waardes die uitgelezen zijn van de lijnsensoren vast houdt.
        int pins[5]; // array die de pinnen vast houdt waaraan de lijnsensoren zijn bevestigd.
};