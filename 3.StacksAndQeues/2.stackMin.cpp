#include <iostream>
using namespace std;

class StackMin {
  struct Node {
    Node * next;
    int data;
    int min;
  };
private:
  Node * top;

public:
  StackMin();
  ~StackMin();
  void push(int data);
  int pop();
  int peak();
  int min();
  bool isEmpty();
};

StackMin::StackMin () {
  top = NULL;
}

StackMin::~StackMin() {
  Node * aux;
  while (top != NULL) {
    aux = top;
    top = top->next;
    delete aux;
  }
}

// Returns 0 if isEmpty
int StackMin::peak () {
  return isEmpty() ? 0 : top->data;
}

void StackMin::push (int data) {
  Node * newTop = new Node;
  newTop->data = data;
  if (top == NULL) {
    newTop->min = data;
    newTop->next = NULL;
  } else {
    newTop->min = data < top->min ? data : top->min;
    newTop->next = top;
  }
  top = newTop;
}

// Returns 0 if isEmpty
int StackMin::pop () {
  if (isEmpty()) {
    return 0;
  }
  int result = top->data;
  Node * aux = top->next;
  delete top;
  top = aux;
  return result;
}

// Returns 0 if isEmpty
int StackMin::min () {
  return isEmpty() ? 0 : top->min;
}

bool StackMin::isEmpty () {
  return top == NULL;
}

int main () {
  StackMin stack;
  stack.push(1);
  stack.push(2);
  stack.push(-1);
  cout << "Mínimo antes:" << stack.min() << endl;
  cout << "Pop:" << stack.pop() << endl;
  cout << "Mínimo despues:" << stack.min() << endl;
}
