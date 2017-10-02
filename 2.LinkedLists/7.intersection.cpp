#include <iostream>
#include <cmath>
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

struct Result {
  bool stillPosible;
  Node * intersection;
};

Result intersectionRecursive (Node * runner1, Node * runner2) {
  Result result;
  if (runner1->next == NULL) {
    result.stillPosible = runner1 == runner2;
    result.intersection = NULL;
  } else {
    result = intersectionRecursive(
          runner1->next == NULL ? runner1 : runner1->next,
          runner2->next == NULL ? runner2 : runner2->next);
  }
  // Still haven't found it:
  if (result.stillPosible && result.intersection == NULL) {
    if (runner1 != runner2) {
      result.intersection = runner1->next;
    }
  }
  return result;
}

Node * intersection (Node * list1, Node * list2) {
  int length1 = length(list1), length2 = length(list2);
  if (length1 > length2) {
    for (int i = length1 - length2; i>0; i--){
      list1 = list1->next;
    }
  } else if (length2 > length1) {
    for (int i = length2 - length1; i>0; i--){
      list2 = list2->next;
    }
  }
  Result result = intersectionRecursive(list1, list2);
  if (result.stillPosible && result.intersection == NULL) {
    return list1;
  }
  return result.intersection;
}

Node * intersectionEasy (Node * list1, Node * list2) {
  int length1 = length(list1), length2 = length(list2);
  if (length1 > length2) {
    for (int i = length1 - length2; i>0; i--){
      list1 = list1->next;
    }
  } else if (length2 > length1) {
    for (int i = length2 - length1; i>0; i--){
      list2 = list2->next;
    }
  }
  Node * intersec = NULL;
  while (intersec == NULL && list1 != NULL) {
    if (list1 == list2) {
      intersec = list1;
    }
  }
  return intersec;
}

int main () {
  Node * list1 = NULL, *list2 = NULL, *result = NULL;
  int vector [4] = {6,7,8,9}, vector2 [3] = {2,5,3};
  addVector(list1, vector, 4);
  list2 = list1;
  addVector(list2, vector2, 3);
  print(list1);
  print(list2);
  result = intersection(list1, list2);
  print(result);
  result = intersectionEasy(list1, list2);
  print(result);

  deleteList(list1);
  deleteList(list2);
  deleteList(result);
}
