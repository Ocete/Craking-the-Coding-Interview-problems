#include <iostream>
using namespace std;

class ArrayList {
private:
  int elems;
  int cap;
  int * v;
public:
  ArrayList(){
    elems = 0;
    cap = 1;
    v = new int [1];
  }

  void add (int n) {
    if (cap == elems) {
      cout << "Aumentando cap de " << cap << " a " << 2*cap << endl;
      int * aux = new int [2*cap];
      for (int i=0;i<cap;i++) {
        aux[i] = v[i];
      }
      delete [] v;
      v = aux;
      cap *= 2;
    }
    v[elems] = n;
    elems++;
  }

  int get (int i) {
    return v[i];
  }

  int getCap() {
    return cap;
  }

  int getElems() {
    return elems;
  }

  ~ArrayList() {
    delete [] v;
  }
};

int main () {
  ArrayList array;
  for (int i=0;i<1000;i++)
    array.add(i);

  cout << array.getCap() << " " << array.getElems() << endl;
  for (int i=0;i<1000;i++)
    cout << array.get(i) << " ";
  cout << endl;
}
