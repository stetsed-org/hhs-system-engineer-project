#include <iostream>
#include <string>

int main() {
  cout << "Program is Initializing"
  // Add more code after here, and switch above to write to Serial.

  auto& xbee = Serial1;
  // While using the same Serial class as the arduino IDE does, add this to be able to do xbee.println() instead of Serial1.println()
}
