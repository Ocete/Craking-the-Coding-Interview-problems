#include <iostream>
#include <string>
using namespace std;

void stringToChar(const string &str, char * &v) {
  if (v != NULL) delete [] v;
  //v = new char [str.size()]; //Para la funcion en general lo queremos asi
  v = new char [100]; //En este caso aprticular reservamos espacio extra
  for (int i=0; i<str.size(); i++)
    v[i] = str[i];
}

void URLify (char * &str, int size, int &newSize) {
  int spaces = 0, j = size-1;
  for (int i=0; i<size; i++) {
    if (str[i] == ' ') spaces++;
  }
  newSize = size + 2*spaces;
  char * aux = new char [newSize];
  for (int i=newSize-1; i>=0; i--) {
    if(str[j] == ' ') {
      aux[i] = '0'; i--;
      aux[i] = '2'; i--;
      aux[i] = '%';
    } else {
      aux[i] = str[j];
    }
    j--;
  }
  for (int i=0; i<newSize; i++) {
    str[i] = aux[i];
  }
  delete [] aux;
}

int main() {
  string str = " hola que tal colega      ";
  int tam = str.size();
  char * vector = NULL;
  stringToChar(str, vector);
  for (int i=0; i<tam; i++)
    cout << vector[i];
  cout << endl;
  URLify(vector, str.size(), tam);
  for (int i=0; i<tam; i++)
    cout << vector[i];
  cout << endl;
}
