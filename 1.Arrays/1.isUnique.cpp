#include <iostream>
#include <string>
using namespace std;

int asciiToInt (char c) {
  return c-'a';
}

bool isUnique (string str) {
  if (str.size() > 256) return false;

  bool aux [256] = {0};
  for (int i=0; i<str.size(); i++) {
    if (aux[asciiToInt(str[i])]) {
      return false;
    } else {
      aux[asciiToInt(str[i])] = true;
    }
  }
  return true;
}

int main() {
  string str = "murcielago";
  cout << "Murcielago: " << isUnique(str) << endl;
  str = "hoola";
  cout << "hoola: " << isUnique(str) << endl;
}
