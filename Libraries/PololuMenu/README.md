# PololuMenu library for Arduino

## Summary

<img align="right" src="https://a.pololu-files.com/picture/0J11105.175w.jpg?b255cdfe056cecdabbae18657574754b">

This is a C++ library for the Arduino IDE that makes it easy to create
basic menus with an 8x2 character LCD, some buttons, and an optional
buzzer to beep when the buttons are pressed.  Adding a menu to your
project with this library will require about 1k of flash.

## Example usage

```cpp
PololuMenu<typeof(lcd)> menu;

void setup()
{
  static const PololuMenuItem items[] = {
    { F("Item one"), myFunction1 },
    { F("Item two"), myFunction2 },
  };

  menu.setItems(items, 2);

  menu.setDisplay(lcd);
  menu.setBuzzer(buzzer);
  menu.setPreviousButton(buttonA, 'A');
  menu.setSelectButton(buttonB, 'B');
  menu.setNextButton(buttonC, 'C');
}

void loop()
{
  menu.select();
}
```

## Recommended devices

* [Pololu 3pi+ 32U4](https://www.pololu.com/3pi+)
* [Pololu Zumo 32U4](https://www.pololu.com/zumo)
* [Pololu Balboa 32U4](https://www.pololu.com/balboa)
* [Pololu A-Star 32U4](https://www.pololu.com/a-star)

This library depends on the
[PololuBuzzer](https://github.com/pololu/pololu-buzzer-arduino), and
[Pushbutton](https://github.com/pololu/pushbutton-arduino) libraries;
it should work on other Arduino platforms that can support these
libraries.  For the Zumo, Balboa, and A-Star 32U4 platforms, these
libraries are included within the corresponding library for the
platform and should not be installed separately.

You will need one of the following display libraries:

* [PololuHD44780](https://github.com/pololu/pololu-hd44780-arduino)
* [PololuOLED](https://github.com/pololu/pololu-oled)

## Version history

* 2.0.0 (2021-08-02): Support multiple types of displays using templating; see the examples for how to use the template. Note that you will also need to change `PololuMenu::Item` to `PololuMenuItem`.
* 1.0.2 (2020-12-03): Added CI testing for GitHub; adapt examples for CI
* 1.0.1 (2020-12-01): Added `const` specification to `setSecondLine()` and `setItems()`; CI testing.
* 1.0.0 (2020-11-24): Initial release.
