#include <iostream>
#include <string>
#include <sstream> //stringstream
using namespace std;

string stringCompression (const string &str) {
  int letters = 1;
  stringstream ss;
  string result;
  for (int i=0; i<str.size(); i++) {
    if (i+1 > str.size() || str[i] != str[i+1]) {
      ss << str[i] << letters;
      letters = 1;
    } else {
      letters++;
    }
  }
  result = ss.str();
  return (result.size() < str.size()) ? result : str;
}

int main() {
  string str = "AAaaVavvvhhhhiii";
  cout << str << endl << stringCompression(str) << endl;
  str = "abcdefghijklmnopqrstuvwxyz";
  cout << str << endl << stringCompression(str) << endl;
}
