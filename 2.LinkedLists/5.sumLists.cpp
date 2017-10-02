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

// Returns 10 ^ (the positition from the tail); the last one is 0
// List = 1 -> 2 -> 3 -> 4  =>  sum = 1234
int concatenateOneListReverse (Node * list, int &sum) {
  if (list == NULL) {
    return 1;
  }
  int ret_value = concatenateOneListReverse(list->next, sum);
  sum += ret_value * list->content;
  return ret_value * 10;
}

// List = 1 -> 2 -> 3 -> 4  =>  sum = 4321
int concatenateOneList (Node * list) {
  Node * aux = list;
  int ret_value = 0, base = 1;
  while (aux != NULL) {
    ret_value += aux->content * base;
    base *= 10;
    aux = aux->next;
  }
  return ret_value;
}

Node * sumLists (Node * list1, Node * list2) {
  int numb1, numb2, result;
  numb1 = concatenateOneList(list1);
  numb2 = concatenateOneList(list2);
  result = numb1 + numb2;
  Node * head = NULL, *tail = NULL, *aux = NULL;
  while (result > 0) {
    aux = new Node;
    if (head == NULL) {
      head = aux;
      tail = aux;
    } else {
      tail->next = aux;
        tail = aux;
    }
    aux->content = result % 10;
    result /= 10;
  }
  tail->next = NULL;
  return head;
}

Node * sumListsReverse (Node * list1, Node * list2) {
  int numb1 = 0, numb2 = 0, result;
  concatenateOneListReverse(list1, numb1);
  concatenateOneListReverse(list2, numb2);
  result = numb1 + numb2;
  Node * head = NULL;
  while (result > 0) {
    add (head, result % 10);
    result = result/10;
  }
  return head;
}

Node * sumLists2 (Node * list1, Node * list2) {
  Node *head = NULL, *runner1 = list1, *runner2 = list2, *tail;
  int acarreo = 0, sum;
  while (runner1 != NULL && runner2 != NULL) {
    if (head == NULL) {
      head = new Node;
      tail = head;
    } else {
      tail->next = new Node;
      tail = tail->next;
    }
    sum = runner1->content + runner2->content + acarreo;
    tail->content = sum % 10;
    acarreo = sum / 10;
    runner1 = runner1->next;
    runner2 = runner2->next;
  }
  if (runner2 != NULL) {
    runner1 = runner2;
  }
  while (runner1 != NULL) {
    tail->next = new Node;
    tail = tail->next;
    tail->content = runner1->content + acarreo;
    acarreo = 0;
    runner1 = runner1->next;
  }
  if (acarreo > 0) {
    tail->next = new Node;
    tail = tail->next;
    tail->content = acarreo;
  }
  tail->next = NULL;
  return head;
}

// Prec: lists shall not be empty
bool sumRecursive (Node * list1, Node * list2, Node * &result, int &acarreo) {
  // Prec.: list1.length = list2.length
  if (list1 == NULL ^ list2 == NULL) {
    return 0;
  }
  int sum;
  if (list1->next == NULL) {
    sum = list1->content + list2->content;
    acarreo = sum / 10;
    add(result, sum % 10);
    return 1;
  }
  sumRecursive(list1->next, list2->next, result, acarreo);
  sum = list1->content + list2->content + acarreo;
  acarreo = sum / 10;
  add(result, sum % 10);
  return 1;
}

// This function may alter the lists if list1.length != list2.length
Node * sumListsReverse2 (Node * &list1, Node * &list2) {
  int length1 = length(list1), length2 = length(list2),
      dif = abs(length1 - length2);
  Node *aux, *head;
  if (dif > 0) {
    if (length1 > length2) {
      head = list1;
    } else {
      head = list2;
    }
    while (dif > 0) {
      aux = head->next;
      aux->content += head->content * 10;
      delete head;
      head = aux;
      dif--;
    }
  }
  head = NULL;
  sumRecursive(list1, list2, head, dif);
  while (dif > 0) {
    add(head, dif%10);
    dif /= 10;
  }
  return head;
}

int main () {
  Node * list1 = NULL, *list2 = NULL, *listR = NULL;
  int vector [3] = {6,1,7}, vector2 [3] = {2,9,5};
  addVector(list1, vector, 3);
  addVector(list2, vector2, 3);
  print(list1);
  print(list2);

  // Approach 1
    cout << endl << "Approach 1:" << endl;
    // First look
    listR = sumLists(list1, list2);
    print(listR);
    // Second look
    listR = sumListsReverse(list1, list2);
    print(listR);

  // Approach 2
    cout << endl << "Approach 2:" << endl;
    // First look
    listR = sumLists2(list1, list2);
    print(listR);
    // Second look
    listR = sumListsReverse2(list1, list2);
    print(listR);

  deleteList(list1);
  deleteList(list2);
  deleteList(listR);
}
