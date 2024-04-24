#include <PololuMenu.h>

// A minimal example of customizable menus using an 8x2 LCD,
// buzzer, and buttons.
//
// Button C moves to the next option; B selects.
//
// Uncomment one of the following sections for your
// platform, or customize your own.

/*
// For Pololu A-Star 32U4
// https://www.pololu.com/a-star

#include <AStar32U4.h>
AStar32U4LCD display;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
*/

/*
// For Pololu A-Star 32U4 with OLED
// https://www.pololu.com/a-star

#include <AStar32U4.h>
#include <PololuOLED.h>

// You will need to modify the pin numbers on the line below
// to indicate what Arduino pins to use to control the display.
// The pins are specified in this order: CLK, MOS, RES, DC, CS.
// Pass 255 for RES, DC, or CS if you are not using them.
PololuSH1106 display(1, 30, 0, 17, 13);

AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
*/

/*
// For Pololu 3pi+ 32U4
// https://www.pololu.com/3pi+

#include <Pololu3piPlus32U4.h>
Pololu3piPlus32U4::LCD display;
Pololu3piPlus32U4::ButtonB buttonB;
Pololu3piPlus32U4::ButtonC buttonC;
*/

/*
// For Pololu Zumo 32U4
// https://www.pololu.com/zumo

#include <Zumo32U4.h>
Zumo32U4LCD display;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
*/

/*
// For Pololu Balboa 32U4
// https://www.pololu.com/balboa

#include <Balboa32U4.h>
Balboa32U4LCD display;
Balboa32U4ButtonB buttonB;
Balboa32U4ButtonC buttonC;
*/

#ifdef __ARDUINO_CI
// For continuous integration testing using arduino-ci:
//  https://github.com/pololu/arduino-ci
#include <AStar32U4.h>
AStar32U4LCD display;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
#endif

PololuMenu<typeof(display)> menu;

void item1()
{
  display.clear();
  display.print("One!");
  delay(1000);
}

void item2()
{
  display.clear();
  display.print("Two!");
  delay(1000);
}

void setup()
{
  // The list of menu items.
  //
  // Strings are stored in flash using the F() macro.  This only works
  // within a function, so we define the menu items in setup().  The
  // static const specifiers ensure that they will remain available
  // after setup() exits.
  static const PololuMenuItem items[] = {
    { F("Item one"), item1 },
    { F("Item two"), item2 },
  };

  // Set up the menu.
  //
  // Note that you must pass in the correct number of items to
  // setItems().  Instead of typing a literal number, you might find
  // it more convenient to have the Arduino compiler compute it
  // automatically with the following formula:
  //
  // sizeof(items)/sizeof(items[0]))
  menu.setItems(items, 2);

  // Attach the LCD and buttons.  All are optional, but there's
  // probably not much reason to use this library without an LCD and
  // at least two buttons.
  menu.setLcd(display);
  menu.setSelectButton(buttonB, 'B');
  menu.setNextButton(buttonC, 'C');
}

void loop()
{
  menu.select();
}
