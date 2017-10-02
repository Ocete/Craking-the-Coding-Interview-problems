#include <iostream>
#include <string>
using namespace std;

struct Node {
  char content;
  Node * next;
};

int charAt (char c) {
  int dif = c - 'a';
  return (dif >= 0 && dif < 128) ? dif : -1;
}

void add (Node * &list, char c) {
  Node * nuevo = new Node;
  nuevo->content = c;
  nuevo->next = list;
  list = nuevo;
}

void addString (Node * &list, const string &str) {
  for (int i=0; i<str.size(); i++)  {
    add(list, str[i]);
  }
}

void print (Node * list) {
  Node * aux = list;
  while (aux != NULL) {
    cout << aux->content << " ";
    aux = aux->next;
  }
  cout << endl;
}

void deleteList (Node * list) {
  Node * aux = list;
  while (list != NULL) {
    aux = list->next;
    delete list;
    list = aux;
  }
}

int main () {
  Node * list = NULL;
  string str = "alocarac aloh";
  addString(list, str);
  print(list);
  deleteList(list);
}
