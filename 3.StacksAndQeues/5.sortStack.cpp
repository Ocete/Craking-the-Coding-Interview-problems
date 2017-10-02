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
/////////////////////////////////////////////////////////////

void swapAndMove (Stack &from, Stack &to) {
  int aux = to.pop();
  to.push(from.pop());
  to.push(aux);
}

bool sortStackBubble(Stack &stack) {
  if (stack.isEmpty()) {
    return 0;
  }
  Stack auxStack;
  bool keepSorting = true;
  while (keepSorting) {
    keepSorting = false;
    auxStack.push(stack.pop());
    while (!stack.isEmpty()) {
      if (auxStack.peak() > stack.peak()) {
        swapAndMove(stack, auxStack);
        keepSorting = true;
      } else {
        auxStack.push(stack.pop());
      }
    }
    if (keepSorting) {
      keepSorting = false;
      stack.push(auxStack.pop());
      while (!auxStack.isEmpty()) {
        if (auxStack.peak() > stack.peak()) {
          swapAndMove(auxStack, stack);
          keepSorting = true;
        } else {
          stack.push(auxStack.pop());
        }
      }
    }
  }
  // If the sorting ended with all the data in auxStack
  if (stack.isEmpty()) {
    while (!auxStack.isEmpty()) {
      stack.push(auxStack.pop());
    }
  }
  return true;
}

bool sortStackEasy(Stack &stack) {
  if (stack.isEmpty()) {
    return 0;
  }
  Stack auxStack;
  int buffer;
  auxStack.push(stack.pop());
  while (!stack.isEmpty()) {
    buffer = stack.pop();
    while (buffer < auxStack.peak()) {
      stack.push(auxStack.pop());
    }
    auxStack.push(buffer);
  }
  while (!auxStack.isEmpty()) {
    stack.push(auxStack.pop());
  }
  return 1;
}

int main() {
  Stack S;
  S.push(2);
  S.push(5);
  S.push(3);
  S.push(8);
  S.push(4);
  S.push(6);
  S.push(5);
  sortStackEasy(S);
  cout << "Insert in order sort:" << endl;
  while (!S.isEmpty()) {
    cout << "Pop: " << S.pop() << endl;
  }
  S.push(2);
  S.push(5);
  S.push(3);
  S.push(8);
  S.push(4);
  S.push(6);
  S.push(5);
  sortStackBubble(S);
  cout << "Bubble sort:" << endl;
  while (!S.isEmpty()) {
    cout << "Pop: " << S.pop() << endl;
  }
}
