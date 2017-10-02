#include <iostream>
using namespace std;

class MultipleStack{
private:
  static const int CAP = 30;
  const int NUM_STACKS;
  int * stack;
  int * elements;
  int index(int stack_index);

public:
  MultipleStack(int num_stacks);
  ~MultipleStack();
  bool push(int stack_index, int data);
  int peak(int stack_index);
  int pop(int stack_index);
  bool isEmpty(int stack_index);
  bool isFull(int stack_index);
};

// stacks indexes start on 0!
// Returns -1 if stack_index is wrong, the position of the last elem.
// in other case
int MultipleStack::index(int stack_index) {
  if (stack_index <= 0 || stack_index > NUM_STACKS) {
    return -1;
  }
  return (stack_index-1) * CAP/NUM_STACKS + elements[stack_index];
}

MultipleStack::MultipleStack(int num_stacks)
    :NUM_STACKS(num_stacks) {
  stack = new int [CAP];
  elements = new int [NUM_STACKS];
  for (int i=0; i<NUM_STACKS; i++) {
    elements[i] = 0;
  }
}

MultipleStack::~MultipleStack() {
  delete [] stack;
  delete [] elements;
}

// Returns 0 if the stack is full or stack_index is wrong;
bool MultipleStack::push(int stack_index, int data) {
  int i = index(stack_index);
  if (isFull(stack_index) || i == -1) {
    return false;
  }
  elements[stack_index]++;
  stack[i] = data;
  return true;
}

// Returns 0 if isEmpty
// Returns -1 if stack_index is wrong
int MultipleStack::peak(int stack_index) {
  int i = index(stack_index);
  if (isEmpty(stack_index)) {
    return 0;
  } else if (i == -1) {
    return -1;
  }
  return stack[i-1];
}

// Returns -1 if sack_index is wrong
// Returns 0 if isEmpty
int MultipleStack::pop(int stack_index) {
  int i = index(stack_index);
  if (i == -1) {
    return -1;
  } else if (isEmpty(stack_index)) {
    return 0;
  }
  elements[stack_index]--;
  return stack[i-1];
}

// Prec.: stack_index correct
bool MultipleStack::isEmpty(int stack_index) {
  return elements[stack_index] == 0;
}

// Prec.: stack_index correct
bool MultipleStack::isFull(int stack_index) {
  return elements[stack_index] == CAP/NUM_STACKS;
}

int main () {
  MultipleStack MS(3);
  cout << MS.push(1, 1) << endl;
  cout << MS.push(1, 2) << endl;
  cout << MS.push(1, 3) << endl;
  cout << MS.push(2, 4) << endl;
  cout << MS.push(2, 5) << endl;
  cout << MS.push(3, 9) << endl;
  cout << "Peak: " << MS.peak(2)  << " " << MS.isEmpty(2) << endl;
  cout << "Pop: " << MS.pop(3) << " " << MS.isEmpty(3) << endl;
  cout << "Pop: " << MS.pop(3) << " " << MS.isEmpty(3) << endl;
  cout << "Peak: " << MS.peak(1)  << " " << MS.isEmpty(1) << endl;
  cout << "Pop: " << MS.pop(1) << " " << MS.isEmpty(1) << endl;
  cout << "Pop: " << MS.pop(3) << " " << MS.isEmpty(3) << endl;

}
