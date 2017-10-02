#include <iostream>
#include <string>
using namespace std;

bool stringRotation (const string &str1, const string &str2) {
  if (str1.size() != str2.size()) {
    return false;
  }
  string aux = str2 + str2;
  return aux.find(str1) != string::npos;
}

int main () {
  string str1 = "waterbottle", str2 = "terbottlewa";
  cout << stringRotation(str1, str2) << endl;
  str2 = "rbottlewate";
  cout << stringRotation(str1, str2) << endl;
  str2 = "rbottlewaet";
  cout << stringRotation(str1, str2) << endl;
}
