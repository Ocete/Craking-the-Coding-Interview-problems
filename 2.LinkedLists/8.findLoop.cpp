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


template <class T>
struct Celda {
	T content;
	Celda * next;
};

template <class T>
class HashTable {
private:
	static const int A_SIZE = 5;
	Celda<T> ** table;

public:
	HashTable ();
	void add (const T &t);
	bool sub (const T &t);
	void print ();
	bool empty();
	int fHash (const T &t);
	~HashTable ();
};

template <class T>
HashTable<T>::HashTable() {
	table = new Celda<T> * [A_SIZE];
	for (int i=0; i<A_SIZE; i++)
		table[i] = NULL;
}

template <class T>
void HashTable<T>::add (const T &t) {
	int i = fHash(t);
	if (table[i] == NULL) {
		table[i] = new Celda<T>;
	} else {
		Celda<T> * aux = new Celda<T>;
		aux->next = table[i];
		table[i] = aux;
	}
	table[i]->content = t;
}

// Returns false if t was not in the hashTable
template <class T>
bool HashTable<T>::sub (const T &t) {
	int i = fHash(t);
	Celda<T> * aux = table[i];
	bool result = aux != NULL;
	if (result) {
		if (aux->content == t) {
			table[i] = table[i]->next;
			delete aux;
		} else {
			result = false;
			while (!result && aux->next != NULL) {
				if (aux->next->content == t) {
					Celda<T> * aux2 = aux->next->next;
					delete aux->next;
					aux->next = aux2;
					result = true;
				} else {
					aux = aux->next;
				}
			}
		}
	}
	return result;
}

template <class T>
void HashTable<T>::print () {
	Celda<T> * aux;
	for (int i=0; i<A_SIZE; i++) {
		cout << "\tTable[" << i << "]" << endl;
		aux = table[i];
		while (aux != NULL) {
			cout << aux->content << endl;
			aux = aux->next;
		}
	}
}

bool empty() {
	bool result = true;
	int i=0;
	while (result && i<A_SIZE) {
		result = table[i] == NULL;
		i++;
	}
	return result;
}

template <class T>
int HashTable<T>::fHash (const T &t) {
	return hash<T>{}(t) % A_SIZE;
}

template <class T>
HashTable<T>::~HashTable () {
	Celda<T> * aux;
	for (int i=0; i<A_SIZE; i++) {
		while (table[i] != NULL) {
			aux = table[i];
			table[i] = table[i]->next;
			delete aux;
		}
	}
	delete [] table;
}

// Returns NULL if there is no loop
Node * findLoop (Node * list) {
   HashTable<int> hashT;
   bool stop = list == NULL;
   Node * runner = list, result = NULL:
   while (!stop && runner != NULL) {
     stop = hashT.sub(runner);
     if (stop) {
       result = runner;
     }
     hashT.add(runner);
   }
   return result;
}

int main () {
  Node * list1 = NULL, *list2 = NULL, *result = NULL;
  int vector [4] = {6,7,8,9}, vector2 [3] = {2,5,3};
  addVector(list1, vector, 4);
  addVector(list2, vector2, 3);
  print(list1);
  print(list2);

  result = findLoop(list1);
  if (result != NULL) {
    print(result);
  } else {
    cout << "LOOP!" << endl;
  }

  result = findLoop(list2);
  if (result != NULL) {
    print(result);
  } else {
    cout << "LOOP!" << endl;
  }

  deleteList(list1);
  deleteList(list2);
}
