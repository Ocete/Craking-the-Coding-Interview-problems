#include <iostream>
#include <string>
#include <functional> //Para la función hash
using namespace std;

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

int main () {
/*
	HashTable ht;
	string s	1 = "hola", s2 = "hola2";
	ht.add(s1);
	ht.add(s1);
	ht.add(s1);
	ht.add(s1);

	ht.print();
	cout << endl << ht.sub(s2) << endl;
	ht.print();
	*/
}
