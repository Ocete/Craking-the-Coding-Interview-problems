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

// Deletes a node from a list, nor the first one nor the last one
// a->b-c-d  deleteMiddleNode('c') a->b->d
bool deleteMiddleNode (Node * node) {
  if (node == NULL || node->next == NULL) {
    return false;
  }
  Node * aux;
  node->content = node->next->content;
  aux = node->next->next;
  delete node->next;
  node->next = aux;
  return true;
}

int main () {
  Node * list = NULL;
  cout << deleteMiddleNode(list) << endl;
  string str = "alocarac aloh";
  addString(list, str);
  print(list);
  deleteMiddleNode(list->next->next);
  print(list);
  deleteMiddleNode(list->next->next->next->next);
  print(list);
  deleteList(list);
}
