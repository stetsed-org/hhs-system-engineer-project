#ifndef _SERIALJSON_H_
#define _SERIALJSON_H_
#include "../headers.hpp"

/** Class for formatting data into the JSON format and sending it over Serial1
 * works with single point of data and arrays
 * To-do: making a function to add multiple data points of the same type.
 *        changing the debug functions of the other classes to use this system
*/
class SerialJSON
{
private:
    String JSONTotal;
    String Spacer = ", ";
    bool firstValue;
    char arrayStart = '[';
    char arrayEnd = ']';
    char JSONEnd = '}';
public:
    SerialJSON();
    ~SerialJSON();

    /** formats the value(long) as part of the key(string)
    */
    void addNewData(String, long);

    /** formats the contents of the array(int*) as part of the key(string)
     * the size of the array that you want to formats needs to be put in
    */
    void addNewData(String, int*, int);

    /** sends the JSON string that has been made over Serial1
     * if none of the addNewData functions have been called it sends a empty JSON string
    */
    void sendJSON();
};

#include "SerialJSON.cpp"
#endif