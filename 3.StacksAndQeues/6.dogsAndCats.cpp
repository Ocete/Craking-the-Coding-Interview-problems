#include <iostream>
#include <string>
using namespace std;

class AnimalShelter {
  struct Node {
    string name;
    unsigned int time;
    Node * next;
  };
private:
  unsigned int time;
  Node * topDog;
  Node * tailDog;
  Node * topCat;
  Node * tailCat;
  string dequeue(Node * &tail, Node * &top);
public:
  AnimalShelter();
  ~AnimalShelter();
  void enqueue(bool isDog, string name);
  string dequeueAny();
  string dequeueDog();
  string dequeueCat();
};

string AnimalShelter::dequeue(Node * &tail, Node * &top) {
  if (top == NULL) {
    return "EMPTY";
  }
  Node * aux;
  string name = top->name;
  aux = top;
  top = top->next;
  delete aux;
  if (top == NULL) {
    tail = NULL;
  }
  return name;
}

AnimalShelter::AnimalShelter() {
  time = 0;
  topDog = NULL;
  topCat = NULL;
}

AnimalShelter::~AnimalShelter() {
  Node * aux;
  while (topDog != NULL) {
    aux = topDog;
    topDog = topDog->next;
    delete aux;
  }
  while (topCat != NULL) {
    aux = topCat;
    topCat = topCat->next;
    delete aux;
  }
}

void AnimalShelter::enqueue(bool isDog, string name) {
  Node * newNode = new Node;
  newNode->name = name;
  newNode->time = time;
  time++;
  newNode->next = NULL;
  if (isDog) {
    if (tailDog == NULL) {
      tailDog = newNode;
      topDog = newNode;
    } else {
      tailDog->next = newNode;
      tailDog = tailDog->next;
    }
  } else {
    if (tailCat == NULL) {
      tailCat = newNode;
      topCat = newNode;
    } else {
      tailCat->next = newNode;
      tailCat = tailCat->next;
    }
  }
}

string AnimalShelter::dequeueAny() {
  if (topDog == NULL) {
    if (topCat == NULL) {
      return "EMPTY";
    } else {
      return dequeueCat();
    }
  } else if (topCat == NULL) {
    return dequeueDog();
  } else if (topDog->time < topCat->time) {
    return dequeueDog();
  } else {
    return dequeueCat();
  }
}

string AnimalShelter::dequeueDog() {
  return dequeue(tailDog, topDog);
}

string AnimalShelter::dequeueCat() {
  return dequeue(tailCat, topCat);
}

int main() {
  AnimalShelter AS;
  AS.enqueue(false, "LAURA");
  AS.enqueue(true, "LUNA");
  AS.enqueue(false, "GHOST");
  AS.enqueue(true, "FLAI");
  AS.enqueue(true, "PACO");
  cout << "Sacamos loquesea: " << AS.dequeueAny() << endl;
  cout << "Sacamos loquesea: " << AS.dequeueAny() << endl;
  cout << "Sacamos perrete: " << AS.dequeueDog() << endl;
  cout << "Sacamos loquesea: " << AS.dequeueAny() << endl;
  cout << "Sacamos gatete: " << AS.dequeueCat() << endl;
  cout << "Sacamos loquesea: " << AS.dequeueAny() << endl;
  cout << "Sacamos loquesea: " << AS.dequeueAny() << endl;
}
