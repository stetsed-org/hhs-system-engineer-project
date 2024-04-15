#include <iostream>
#include <string>

using namespace std;

int main() {
  // Send something to standard out buffer, terminal dipshit
  cout << "Fuckme\n";
  // Input from terminal
  string userinput1;
  cout << "Input bitch\n";
  cin >> userinput1;


  // Variables
  int int1 = 69;
  char char1 = 'a';
  float float1 = 1.69;
  bool bool1 = true;
  // First is without string library, second is with string library
  char stringchar[4] = "abc";
  string stringstring1 = "abcdefghjhe";

  cout << stringchar << "\n";
  cout << stringstring1 << "\n";

  // Test Area
  string concatstring = userinput1 + userinput1;

  cout << concatstring << "\n";

  // Return a error code, 0 = success, 0 < some form of fail
  return 0;
}


