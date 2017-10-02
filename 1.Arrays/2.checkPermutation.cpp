#include <iostream>
#include <string>
using namespace std;

int charAt(char c) {
  return c-'a';
}

bool checkPermutation(const string &s1, const string &s2) {
  if (s1.size() != s2.size()) return false;
  char aux [256] = {0};
  int j;
  for (int i=0; i<s1.size(); i++) {
    aux[charAt(s1[i])]++;
  }
  for (int i=0; i<s1.size(); i++) {
    j = charAt(s2[i]);
    aux[j]--;
    if (aux[j] < 0) {
      return false;
    }
  }
  return true;
}

int main(int argc, char const *argv[]) {
  string s1 = "h olas", s2 = "hlaoa ";
  cout << checkPermutation(s1, s2) << endl;
}
