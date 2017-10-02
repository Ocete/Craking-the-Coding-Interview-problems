#include <iostream>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
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
  void print();
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
  top = NULL;
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

template <class T>
void Queue<T>::print() {
  Node * aux = tail;
  while (aux != NULL) {
    cout << aux->data->getData() << " ";
    aux = aux->next;
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
class Project {
private:
  bool built;
  bool buildable;
  int data;
  int num_depen;
  Project ** dependencias;
  const bool indexCorrect(int i);
  bool isBuildable();
public:
  Project(int data_in);
  Project();
  ~Project();
  void addDepen(Project * child);
  const int getData();
  const int getNumdependencias();
  Project * getChild (int index);
  const void print();
  bool buildProject();
};

const bool Project::indexCorrect(int i) {
  return i >= 0 && i < num_depen;
}

Project::Project() {
  built = false;
  buildable = true;
  num_depen = 0;
  dependencias = NULL;
  data = 0;
}

Project::Project(int data_in) :Project() {
  data = data_in;
}

// Unicamente se borra a si mismo, no a sus dependencias
Project::~Project() {
  if (dependencias != NULL) {
      delete [] dependencias;
  }
  dependencias = NULL;
}

void Project::addDepen(Project * new_depen) {
  Project ** aux = new Project*[num_depen+1];
  for (int i=0; i<num_depen; i++) {
        aux[i] = dependencias[i];
  }
  aux[num_depen] = new_depen;
  num_depen++;
  delete [] dependencias;
  dependencias = aux;
}

const int Project::getData() {
  return data;
}

const int Project::getNumdependencias() {
  return num_depen;
}

Project * Project::getChild (int index) {
  Project backUp(-1);
  return indexCorrect(index) ? dependencias[index] : &backUp;
}

bool Project::isBuildable() {
  if (!buildable) {
    buildable = true;
    int i=0;
    while (buildable && i<num_depen) {
      buildable &= dependencias[i]->built;
      i++;
    }
  }
  return buildable;
}

const void Project::print() {
  for (int i=0; i<num_depen; i++) {
    cout << data << " depende de -> " << dependencias[i]->data << endl;
  }
}

bool Project::buildProject() {
  if (!built && isBuildable()) {
    built = true;
  }
  return built;
}
////////////////////////////////////////////////////////////////////////////////
class Graph {
private:
  int num_projects;
  Project ** projects;
  const bool indexCorrect(int i);
public:
  Graph();
  ~Graph();
  void addProject(int data);
  void addDepen(int index_father, int index_child);
  const void print();
  Queue<Project *> * buildOrder();
};

const bool Graph::indexCorrect(int i) {
  return i >= 0 && i < num_projects;
}

Graph::Graph() {
  num_projects = 0;
  projects = NULL;
}

Graph::~Graph() {
  for (int i=0; i<num_projects; i++) {
    delete projects[i];
  }
  delete [] projects;
}

void Graph::addProject(int data) {
  Project * new_project = new Project(data);
  Project ** aux = new Project*[num_projects+1];
  for (int i=0; i<num_projects; i++) {
        aux[i] = projects[i];
  }
  aux[num_projects] = new_project;
  num_projects++;
  delete [] projects;
  projects = aux;
}

void Graph::addDepen(int index_father, int index_child) {
  if (!indexCorrect(index_father) || !indexCorrect(index_child)) {
    return;
  }
  projects[index_father]->addDepen(projects[index_child]);
}

const void Graph::print() {
  for (int i=0; i<num_projects; i++) {
    projects[i]->print();
  }
}

Queue<Project *> * Graph::buildOrder () {
  Queue<Project *> *projectsQ = new Queue<Project *>,
      *order = new Queue<Project *>;
  int p_to_build = num_projects, i, p_to_build_updated = num_projects;
  bool keepBuilding = true;
  Project * aux;
  for (int i=0; i<num_projects; i++) {
    projectsQ->add(projects[i]);
  }
  while (keepBuilding) {
    i=0;
    keepBuilding = false;
    while(i<p_to_build) {
      aux = projectsQ->remove();
      if (aux->buildProject()) {
        keepBuilding = true;
        p_to_build_updated--;
        order->add(aux);
      } else {
        projectsQ->add(aux);
      }
      i++;
    }
    p_to_build = p_to_build_updated;
  }


  return p_to_build == 0 ? order : NULL;
}
////////////////////////////////////////////////////////////////////////////////
int main() {
  Graph graph;
  graph.addProject(0);
  graph.addProject(1);
  graph.addProject(2);
  graph.addProject(3);
  graph.addDepen(0,1);
  graph.addDepen(0,2);
  graph.addDepen(1,3);
  graph.addDepen(2,3);
  graph.print();

  Queue<Project *> * Q = graph.buildOrder();
  cout << endl << "Order (from right to left): " << endl;

  Q->print();
  cout << endl;
}
