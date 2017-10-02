#include <iostream>
using namespace std;

int charAt (char c) {
  return c-'a';
}

void stringToChar(const string &str, char * &v) {
  if (v != NULL) delete [] v;
  v = new char [str.size()];
  for (int i=0; i<str.size(); i++)
    v[i] = str[i];
}

bool checkPalindrome(char * vector, int tam) {
  bool joker = tam % 2 + 1;
  int * aux = new int [256];
  for (int i=0; i<tam; i++) {
    aux[charAt(vector[i])]++;
  }
  for (int i=0; i<256; i++) {
    if (aux[i]%2 != 0) {
      if (!joker) {
        joker = true;
      } else {
        return false;
      }
    }
  }
  return true;
}

int main() {
  string str = "holaalohgg ";
  char * v = NULL;
  stringToChar(str, v);
  cout << "Palindromo:" << checkPalindrome(v, str.size()) << endl;
}
