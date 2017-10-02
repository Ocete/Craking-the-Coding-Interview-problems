#include <iostream>
using namespace std;

struct Node {
  int content;
  Node * next;
};

void add (Node * &list, int i) {
  Node * nuevo = new Node;
  nuevo->content = i;
  nuevo->next = list;
  list = nuevo;
}

void addNode (Node * &list, Node * node) {
  node->next = list;
  list = node;
}

void addVector (Node * &list, int * vector, int tam) {
  for (int i=0; i<tam; i++)  {
    add(list, vector[i]);
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

// Makes a partition of list around elem
void partition (Node * &list, int elem) {
  Node *headGreater = NULL, *headLower = NULL, *tail = NULL, *aux;
  while (list != NULL) {
    aux = list->next;
    if (list->content < elem) {
      addNode(headLower, list);
      if (tail == NULL) {
        tail = headLower;
      }
    } else {
      addNode(headGreater, list);
    }
    list = aux;
  }
  if (tail != NULL) {
    tail->next = headGreater;
  }
  list = headLower;
}

int main () {
  Node * list = NULL;
  partition(list,5); // Empty list doesn't crush
  int vector [7] = {1,2,10,5,8,5,3};
  addVector(list, vector, 7);
  print(list);
  partition(list, 5);
  print(list);
  deleteList(list);
}
