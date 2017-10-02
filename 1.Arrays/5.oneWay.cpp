#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool oneWayEqualSize (const string &s1, const string &s2) {
  bool joker = 0;
  for (int i=0; i<s1.size(); i++) {
      if (s1[i] != s2[i]) {
        if (joker) {
          return false;
        }
        joker = 1;
      }
  }
  return true;
}

bool oneWayNotEqualSize (const string &s1, const string &s2) {
  bool joker=0;
  int j=0;
  for (int i=0; i<s2.size(); i++) {
    //cout << s2.size() << i << j << joker << endl;
    if (s1[i] != s2[j]) {
      if (joker) {
        return false;
      }
      joker = true;
    } else {
      j++;
    }
  }
  //cout << s2.size() << s1 << s2 << joker << endl;
  return (!joker || s1[s1.size()-1] == s2[s2.size()-1]);
}

bool oneWay (const string &s1, const string &s2) {
  // Creamos los siguientes ints porque si no da problemas la diferencia
  int size1 = s1.size(), size2 = s2.size(), dif = abs(size1 - size2);
  if (dif > 1) {
    return false;
  } else if (dif == 0) {
    return oneWayEqualSize(s1, s2);
  } else {
    if (size1 > size2) {
      return oneWayNotEqualSize (s1, s2);
    } else {
      return oneWayNotEqualSize (s2, s1);
    }
  }
}

int main() {
  string s1 = "hola", s2 = "hola";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "hola", s2 = "hoha";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "hohs", s2 = "hola";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "hola", s2 = "hbla";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "hol", s2 = "hola";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "ho", s2 = "hola";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "hol", s2 = "hoha";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "hola", s2 = "hla";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
  s1 = "holamundo", s2 = "holamundoa";
  cout << s1 << "\t" << s2 << "\t" << oneWay(s1, s2) << endl;
}
