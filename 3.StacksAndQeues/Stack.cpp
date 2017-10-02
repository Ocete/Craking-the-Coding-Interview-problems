#include <iostream>
using namespace std;

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
  int pop();
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
int Stack::pop() {
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

int main() {
  Stack S;
  cout << "Peak: " << S.peak()  << " " << S.isEmpty() << endl;
  cout << "Pop: " << S.pop() << " " << S.isEmpty() << endl;
  S.push(1);
  S.push(2);
  S.push(3);
  S.push(4);
  S.push(5);
  cout << "Peak: " << S.peak()  << " " << S.isEmpty() << endl;
  cout << "Pop: " << S.pop() << " " << S.isEmpty() << endl;
  cout << "Pop: " << S.pop() << " " << S.isEmpty() << endl;
}
