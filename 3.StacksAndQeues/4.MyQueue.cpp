#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////

class Stack{
  struct Node {
    int data;
    Node * next;
  };
private:
  Node * top;
public:
  Stack();
  ~Stack();
  void push(int data);
  int remove();
  int peak();
  bool isEmpty();
};

Stack::Stack() {
  top = NULL;
}

Stack::~Stack() {
  Node * aux = top;
  while (top != NULL) {
    aux = top;
    top = top->next;
    delete aux;
  }
}

void Stack::push (int data) {
  Node * aux = new Node;
  aux->next = top;
  top = aux;
  top->data = data;
}

// Returns 0 if isEmpty
int Stack::peak() {
  if (isEmpty()) {
    return 0;
  }
  return top->data;
}

// Returns 0 if isEmpty
int Stack::remove() {
  if (isEmpty()) {
    return 0;
  }
  Node * aux = top;
  top = top->next;
  int ret_val = aux->data;
  delete aux;
  return ret_val;
}

bool Stack::isEmpty() {
  return top == NULL;
}
//////////////////////////////////////////////////////////////////////

class MyQueue {
private:
  Stack MainStack, AuxStack;
  void shiftStacks();
public:
  //MyQueue();
  //~MyQueue(); The stacks clean themselves already
  void add(int data);
  int remove();
  int peak();
  bool isEmpty();
};

void MyQueue::shiftStacks() {
  if (AuxStack.isEmpty()) {
    while (!MainStack.isEmpty()) {
      AuxStack.push(MainStack.remove());
    }
  }
}

void MyQueue::add(int data) {
  MainStack.push(data);
}

// Returns 0 if isEmpty
int MyQueue::remove() {
  shiftStacks();
  return AuxStack.remove();
}

// Returns 0 if isEmpty
int MyQueue::peak() {
  shiftStacks();
  return AuxStack.peak();
}

bool MyQueue::isEmpty() {
  return MainStack.isEmpty() && AuxStack.isEmpty();
}

int main() {
  MyQueue Q;
  cout << "Peak: " << Q.peak()  << " " << Q.isEmpty() << endl;
  cout << "Remove: " << Q.remove() << " " << Q.isEmpty() << endl;
  Q.add(1);
  Q.add(2);
  cout << "Peak: " << Q.peak()  << " " << Q.isEmpty() << endl;
  Q.add(3);
  cout << "Remove: " << Q.remove() << " " << Q.isEmpty() << endl;
  cout << "Remove: " << Q.remove() << " " << Q.isEmpty() << endl;
  Q.add(4);
  Q.add(5);
  cout << "Peak: " << Q.peak()  << " " << Q.isEmpty() << endl;
}
