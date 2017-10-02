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
class Graph {
private:
  int num_nodes;
  GraphNode ** nodes;
  const bool indexCorrect(int i);
public:
  Graph();
  ~Graph();
  void markGraph(bool mark);
  void addNode(int data);
  void addChild(int index_father, int index_child);
  const void print();
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
    delete nodes[i];
  }
  delete [] nodes;
}

void Graph::markGraph(bool mark) {
  for (int i=0; i<num_nodes; i++) {
    nodes[i]->setMark(mark);
  }
}

void Graph::addNode(int data) {
  GraphNode * new_node = new GraphNode(data);
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
////////////////////////////////////////////////////////////////////////////////
int main() {
  Graph Graph;
  Graph.addNode(1);
  Graph.addNode(2);
  Graph.addNode(3);
  Graph.addNode(4);
  Graph.addNode(5);
  Graph.addChild(0,1);
  Graph.addChild(0,2);
  Graph.addChild(2,1);
  Graph.addChild(1,2);
  Graph.addChild(1,3);
  Graph.print();
}
