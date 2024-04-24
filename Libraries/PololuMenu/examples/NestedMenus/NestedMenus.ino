#include <PololuMenu.h>

// A more complicated menu example, with two levels of nested menus.
//
// Uncomment one of the following sections for your
// platform, or customize your own.

/*
// For Pololu A-Star 32U4
// https://www.pololu.com/a-star

#include <AStar32U4.h>
AStar32U4LCD display;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
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

AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
*/

/*
// For Pololu 3pi+ 32U4
// https://www.pololu.com/3pi+

#include <Pololu3piPlus32U4.h>
Pololu3piPlus32U4::LCD display;
Pololu3piPlus32U4::Buzzer buzzer;
Pololu3piPlus32U4::ButtonA buttonA;
Pololu3piPlus32U4::ButtonB buttonB;
Pololu3piPlus32U4::ButtonC buttonC;
*/

/*
// For Pololu Zumo 32U4
// https://www.pololu.com/zumo

#include <Zumo32U4.h>
Zumo32U4LCD display;
Zumo32U4Buzzer buzzer;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
*/

/*
// For Pololu Balboa 32U4
// https://www.pololu.com/balboa

#include <Balboa32U4.h>
Balboa32U4LCD display;
Balboa32U4Buzzer buzzer;
Balboa32U4ButtonA buttonA;
Balboa32U4ButtonB buttonB;
Balboa32U4ButtonC buttonC;
*/

#ifdef __ARDUINO_CI
// For continuous integration testing using arduino-ci:
//  https://github.com/pololu/arduino-ci
#include <AStar32U4.h>
AStar32U4LCD display;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
#endif

PololuMenu<typeof(display)> mainMenu;
PololuMenu<typeof(display)> subMenu;
PololuMenu<typeof(display)> *activeMenu = &mainMenu;

bool anyButtonPress()
{
  if(mainMenu.buttonMonitor())
    return true;

  if(buttonC.getSingleDebouncedPress())
  {
    buzzer.play("!c32");
    return true;
  }

  return false;
}

void item1()
{
  display.clear();
  display.print("This is");
  display.gotoXY(0,1);
  display.print("item one");
  while(!anyButtonPress());
}

void item21()
{
  display.clear();
  display.print("This is");
  display.gotoXY(0,1);
  display.print("item 2.1");
  while(!anyButtonPress());
}

void item22()
{
  display.clear();
  display.print("This is");
  display.gotoXY(0,1);
  display.print("item 2.2");
  while(!anyButtonPress());
}

void openSubMenu()
{
  activeMenu = &subMenu;
  subMenu.restart();
}

void closeSubMenu()
{
  activeMenu = &mainMenu;
}

void setup()
{
  static const PololuMenuItem items[] = {
    { F("Item 1"), item1 },
    { F("2.x ..."), openSubMenu },
  };

  mainMenu.setItems(items, 2);
  mainMenu.setLcd(display);
  mainMenu.setBuzzer(buzzer);
  mainMenu.setSelectButton(buttonB, 'B');
  mainMenu.setNextButton(buttonA, 'A');
  mainMenu.setSecondLine(F("A> B*"));

  static const PololuMenuItem subMenuItems[] = {
    { F("Item 2.1"), item21 },
    { F("Item 2.2"), item22 },
  };

  subMenu.setItems(subMenuItems, 2);
  subMenu.setLcd(display);
  subMenu.setBuzzer(buzzer);
  subMenu.setSelectButton(buttonB, 'B');
  subMenu.setNextButton(buttonA, 'A');
  subMenu.setSecondLine(F("A> B* C<"));
}

void loop()
{
  activeMenu->select();

  // button C exits from the submenu
  if(activeMenu == &subMenu && buttonC.getSingleDebouncedPress())
  {
    buzzer.play("!l32gec");
    closeSubMenu();
  }
}
