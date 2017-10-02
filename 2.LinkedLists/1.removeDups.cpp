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

// Returns 0 if list is NULL, 1 in any other case
bool removeDups (Node * list) {
  if (list == NULL) {
    return false;
  }
  bool * hash = new bool [128];
  Node * p = list, *aux;
  int pos = charAt(p->content);
  bool continuar;
  for (int i=0; i<128; i++) {
    hash[i] = false;
  }
  if (pos != -1) {
    hash[pos] = true;
  }
  while (p->next != NULL) {
    pos = charAt(p->next->content);
    continuar = true;
    if (pos != -1) {
      if (hash[pos]) {
        aux = p->next->next;
        delete p->next;
        p->next = aux;
        continuar = false;
      } else {
        hash[pos] = true;
      }
    }
    if (continuar) {
      p = p->next;
    }
  }
  return true;
}

// Returns 0 if list is NULL, 1 in any other case
bool removeDups2 (Node * list) {
  if (list == NULL) {
    return false;
  }
  Node * p1 = list, *p2, *aux;
  while (p1 != NULL && p1->next != NULL) {
    p2 = p1;
    while (p2->next != NULL) {
      if (p1->content == p2->next->content) {
        aux = p2->next->next;
        delete p2->next;
        p2->next = aux;
      } else {
        p2 = p2->next;
      }
    }
    p1 = p1->next;
  }
  return true;
}

int main () {
  Node * list = NULL;
  string str = "alocarac aloh";
  addString(list, str);
  addString(list, str);
  print(list);
  removeDups(list);
  print(list);

  Node * list2 = NULL;
  addString(list2, str);
  addString(list2, str);
  print(list2);
  removeDups2(list2);
  print(list2);

  deleteList(list);
}
