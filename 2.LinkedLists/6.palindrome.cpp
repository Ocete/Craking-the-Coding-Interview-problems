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

void deleteList (Node * list) {
  Node * aux = list;
  while (list != NULL) {
    aux = list->next;
    delete list;
    list = aux;
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

int length (Node * list) {
  Node * runner = list;
  int l = 0;
  while (runner != NULL) {
    l++;
    runner = runner->next;
  }
  return l;
}

bool palindromeRecursive (Node * &runner, Node * actual) {
  bool palindrome;
  if (actual->next == NULL) {
    palindrome = runner->content == actual->content;
    runner = runner->next;
    return palindrome;
  } else {
    palindrome = palindromeRecursive(runner, actual->next);
  }
  palindrome = palindrome && (runner->content == actual->content);
  runner = runner->next;
  return palindrome;
}

bool palindrome (Node * list) {
  return palindromeRecursive(list, list);
}

int main () {
  Node * list1 = NULL, *list2 = NULL;
  int vector [4] = {6,7,7,6}, vector2 [3] = {2,9,3};
  addVector(list1, vector, 4);
  addVector(list2, vector2, 3);
  print(list1);
  print(list2);

  cout << palindrome(list1) << "\t" << palindrome(list2) << endl;

  deleteList(list1);
  deleteList(list2);
}
