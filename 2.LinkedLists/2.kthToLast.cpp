#include <iostream>
#include <string>
using namespace std;

struct Node {
  char content;
  Node * next;
};

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

// Returns '#' if "list.lenght() < posToLast"
// posToLast = 0 means the last one itself
char kthToLast (Node * list, int posToLast) {
  if (list == NULL) {
    return '#';
  }
  Node * p1 = list, *p2 = p1;
  int moves = 0;
  while (p2->next != NULL && moves < posToLast) {
    p2 = p2->next;
    moves++;
  }
  if (moves != posToLast) {
    return '#';
  }
  while (p2->next != NULL) {
    p1 = p1->next;
    p2 = p2->next;
  }
  return p1->content;
}

int main () {
  Node * list = NULL;
  string str = "alocarac aloh";
  addString(list, str);
  print(list);
  cout << endl << "Pos 3th to last: " << kthToLast(list, 2) << endl;
  cout << endl << "Pos 11th to last: " << kthToLast(list, 21) << endl;
  deleteList(list);
}
