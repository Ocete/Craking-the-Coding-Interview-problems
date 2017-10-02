#include <iostream>
using namespace std;

class PlatesStack {
  struct Node {
    Node * next;
    int * stack;
    int plates;
  };

private:
  const static int MAX_PLATES = 2;
  Node * top;
public:
  PlatesStack();
  ~PlatesStack();
  void add(int data);
  int pop();
  int peak();
  bool isEmpty();
  int popAt(int index);
};

PlatesStack::PlatesStack() {
  top = new Node;
  top->next = NULL;
  top->stack = new int [MAX_PLATES];
  top->plates = 0;
}

PlatesStack::~PlatesStack() {
  Node * aux = top;
  while (top != NULL) {
    aux = top;
    top = top->next;
    delete [] aux->stack;
    delete aux;
  }
}

bool PlatesStack::isEmpty() {
  return top->plates == 0 && top->next == NULL;
}

//Returns 0 if isEmpty
int PlatesStack::peak() {
  if (top->plates != 0) {
    return top->stack[top->plates-1];
  } else if (top->next == NULL) {
    return 0;
  } else {
    return top->next->stack[top->plates-1];
  }
}

void PlatesStack::add(int data) {
  if (top->plates == MAX_PLATES) {
    Node * aux = new Node;
    aux->next = top;
    top = aux;
    top->stack = new int [MAX_PLATES];
    top->plates = 0;
  }
  top->stack[top->plates] = data;
  top->plates++;
}

// Returns 0 if isEmpty
int PlatesStack::pop() {
  if (isEmpty()) {
    return 0;
  } else if (top->plates == 0) {
    Node * aux = top;
    top = top->next;
    delete [] aux->stack;
    delete aux;
  }
  top->plates--;
  return top->stack[top->plates];
}

// Calls pop() if index <= 0
// Returns 0 if stack i is empty
// Returns -1 if there are less than i stacks
// In order to make this O(1), I should have used a ArrayList instead
// of a list of celds.
int PlatesStack::popAt (int index) {
  if (index <= 0) {
    return pop();
  }
  Node * aux = top;
  int j=1;
  while (j < index && aux->next != NULL) {
    aux = aux->next;
    j++;
  }
  if (index != j) {
    return -1;
  } else if (aux->next->plates == 0) {
    return 0;
  }
  aux->next->plates--;
  j = aux->next->stack[aux->next->plates];
  if (aux->next->plates == 0) {
    Node * auxD = aux->next->next;
    delete [] aux->next->stack;
    delete aux->next;
    aux->next = auxD;
  }
  return j;
}

int main() {
  PlatesStack PS;
  cout << "Peak: " << PS.peak()  << " " << PS.isEmpty() << endl;
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl;
  PS.add(1);
  PS.add(2);
  PS.add(3);
  PS.add(4);
  PS.add(5);
  cout << "Peak: " << PS.peak()  << " " << PS.isEmpty() << endl;
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl;
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl;
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl;
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl;
  PS.add(6);
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl;
  cout << "Pop: " << PS.pop() << " " << PS.isEmpty() << endl; // Las funciones se ejecutan desordenadas.
  cout << "isEmpty: " << PS.isEmpty() << endl;
  PS.add(1);
  PS.add(2);
  PS.add(3);
  PS.add(4);
  PS.add(5);
  cout << "PopAt 1: " << PS.popAt(1) << " " << PS.isEmpty() << endl;
  cout << "PopAt 1: " << PS.popAt(1) << " " << PS.isEmpty() << endl;
  cout << "PopAt -1: " << PS.popAt(-1) << " " << PS.isEmpty() << endl;
  cout << "PopAt 0: " << PS.popAt(0) << " " << PS.isEmpty() << endl;
  cout << "PopAt 10: " << PS.popAt(10) << " " << PS.isEmpty() << endl;
}
