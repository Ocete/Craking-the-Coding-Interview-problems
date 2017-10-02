#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
class GraphNode {
private:
  bool mark;
  int data;
  int num_children;
  GraphNode ** children;
  const bool indexCorrect(int i);
public:
  GraphNode(int data_in);
  GraphNode();
  ~GraphNode();
  void addChild(GraphNode * child);
  const int getData();
  const int getNumChildren();
  GraphNode * getChild (int index);
  const bool getMark();
  void setMark(bool mark_in);
  const void print();
};

const bool GraphNode::indexCorrect(int i) {
  return i >= 0 && i < num_children;
}

GraphNode::GraphNode() {
  num_children = 0;
  children = NULL;
  data = 0;
}

GraphNode::GraphNode(int data_in) :GraphNode() {
  data = data_in;
}

// Unicamente se borra a si mismo, no a sus hijos
GraphNode::~GraphNode() {
  //cout << "DELETING NODE " << data << endl;
  if (children != NULL) {
      delete [] children;
  }
}

void GraphNode::addChild(GraphNode * new_child) {
  GraphNode ** aux = new GraphNode*[num_children+1];
  for (int i=0; i<num_children; i++) {
        aux[i] = children[i];
  }
  aux[num_children] = new_child;
  num_children++;
  delete [] children;
  children = aux;
}

const int GraphNode::getData() {
  return data;
}

const int GraphNode::getNumChildren() {
  return num_children;
}

GraphNode * GraphNode::getChild (int index) {
  GraphNode backUp(-1);
  return indexCorrect(index) ? children[index] : &backUp;
}

const bool GraphNode::getMark() {
  return mark;
}

void GraphNode::setMark(bool mark_in) {
  mark = mark_in;
}

const void GraphNode::print() {
  for (int i=0; i<num_children; i++) {
    cout << data << " -> " << children[i]->data << endl;
  }
}
////////////////////////////////////////////////////////////////////////////////
class Queue {
  struct Node {
    Node * next;
    GraphNode * data;
  };
private:
  Node * top;
  Node * tail;
public:
  Queue();
  ~Queue();
  void add(GraphNode * data);
  GraphNode * peak();
  GraphNode * remove();
  bool isEmpty();
};

Queue::Queue() {
  top = NULL;
  tail = NULL;
}

Queue::~Queue() {
  Node * aux = top;
  while (!isEmpty()) {
    aux = top;
    top = top->next;
    delete aux;
  }
}

void Queue::add(GraphNode * data) {
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
GraphNode * Queue::peak() {
  if (isEmpty()) {
    return 0;
  }
  return tail->data;
}

// Returns 0 if isEmpty
GraphNode * Queue::remove() {
  if (isEmpty()) {
    return 0;
  }
  Node * aux = tail;
  GraphNode * ret_val = tail->data;
  tail = tail->next;
  delete aux;
  if (tail == NULL) {
    top = NULL;
  }
  return ret_val;
}

bool Queue::isEmpty() {
  return top == NULL;
}
////////////////////////////////////////////////////////////////////////////////
class Graph {
private:
  int num_nodes;
  GraphNode ** nodes;
  const bool indexCorrect(int i);
  const bool routeFromTo(int index_from, int index_to);
public:
  Graph();
  ~Graph();
  void markGraph(bool mark);
  void addNode(GraphNode * new_node);
  void addChild(int index_father, int index_child);
  const void print();
  const bool routeBetweenNodes(int index1, int index2);
};

const bool Graph::indexCorrect(int i) {
  return i >= 0 && i < num_nodes;
}

Graph::Graph() {
  num_nodes = 0;
  nodes = NULL;
}

Graph::~Graph() {
  for (int i=0; i<num_nodes; i++) {
    //cout << "GRAPH DELETES NODE " << i << endl;
    //delete nodes[i];
  }
  delete [] nodes;
}

void Graph::markGraph(bool mark) {
  for (int i=0; i<num_nodes; i++) {
    nodes[i]->setMark(mark);
  }
}

void Graph::addNode(GraphNode * new_node) {
  GraphNode ** aux = new GraphNode*[num_nodes+1];
  for (int i=0; i<num_nodes; i++) {
        aux[i] = nodes[i];
  }
  aux[num_nodes] = new_node;
  num_nodes++;
  delete [] nodes;
  nodes = aux;
}

void Graph::addChild(int index_father, int index_child) {
  if (!indexCorrect(index_father) || !indexCorrect(index_child)) {
    return;
  }
  nodes[index_father]->addChild(nodes[index_child]);
}

const void Graph::print() {
  for (int i=0; i<num_nodes; i++) {
    nodes[i]->print();
  }
}

// Prec.: indexes correct
const bool Graph::routeFromTo(int index_from, int index_to) {
  markGraph(false);
  Queue Q;
  GraphNode *current, *aux;
  int tope;
  Q.add(nodes[index_from]);
  nodes[index_from]->setMark(true);
  while(!Q.isEmpty()) {
    current = Q.remove();
    tope = current->getNumChildren();
    for (int i=0; i<tope; i++) {
      aux = current->getChild(i);
      if (!aux->getMark()) {
        if (aux == nodes[index_to]) {
          return true;
        }
        aux->setMark(true);
        Q.add(aux);
      }
    }
  }
  return false;
}

const bool Graph::routeBetweenNodes(int index1, int index2) {
  if (!indexCorrect(index1) || !indexCorrect(index2)) {
    return false;
  } else if (index1 == index2) {
    return true;
  }
  return routeFromTo(index1, index2) || routeFromTo(index2, index1);
}
////////////////////////////////////////////////////////////////////////////////
int main() {
  GraphNode G1(1), G2(2), G3(3), G4(4), G5(5);
  Graph Graph;
  Graph.addNode(&G1);
  Graph.addNode(&G2);
  Graph.addNode(&G3);
  Graph.addNode(&G4);
  Graph.addNode(&G5);
  Graph.addChild(0,1);
  Graph.addChild(0,2);
  Graph.addChild(2,1);
  Graph.addChild(1,2);
  Graph.addChild(1,3);
  Graph.print();
  cout << "Route between 1,4: " << Graph.routeBetweenNodes(0,3) << endl;
  cout << "Route between 1,5: " << Graph.routeBetweenNodes(0,4) << endl;
}
