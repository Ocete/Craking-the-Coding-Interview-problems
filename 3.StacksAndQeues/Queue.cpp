#include <iostream>
using namespace std;

template <class T>
class Queue {
  struct Node {
    Node * next;
    T data;
  };
private:
  Node * top;
  Node * tail;
public:
  Queue();
  ~Queue();
  void add(T data);
  T peak();
  T remove();
  bool isEmpty();
};

template <class T>
Queue<T>::Queue() {
  top = NULL;
  tail = NULL;
}

template <class T>
Queue<T>::~Queue() {
  Node * aux = top;
  while (!isEmpty()) {
    aux = top;
    top = top->next;
    delete aux;
  }
}

template <class T>
void Queue<T>::add(T data) {
  Node * newNode = new Node;
  newNode->data = data;
  newNode->next = NULL;
  if (isEmpty()) {
    top = newNode;
    tail = newNode;
  } else {
    top->next = newNode;
    top = top->next;
  }
}

// Returns 0 if isEmpty
template <class T>
T Queue<T>::peak() {
  if (isEmpty()) {
    return 0;
  }
  return tail->data;
}

// Returns 0 if isEmpty
template <class T>
T Queue<T>::remove() {
  if (isEmpty()) {
    return 0;
  }
  Node * aux = tail;
  T ret_val = tail->data;
  tail = tail->next;
  delete aux;
  return ret_val;
}

template <class T>
bool Queue<T>::isEmpty() {
  return top == NULL;
}

int main() {
  Queue<int> Q;
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
