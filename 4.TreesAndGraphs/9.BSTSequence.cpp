#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
struct Node {
  int data;
  Node * next;
};


void add (Node * &list, char c) {
  Node * nuevo = new Node;
  nuevo->data = c;
  nuevo->next = list;
  list = nuevo;
}

void addString (Node * &list, const string &str) {
  for (int i=0; i<str.size(); i++)  {
    add(list, str[i]);
  }
}

void print (Node * list) {
  Node * aux = list;
  while (aux != NULL) {
    cout << aux->data << " ";
    aux = aux->next;
  }
  cout << endl;
}

void deleteList (Node * list) {
  Node * aux = list;
  while (list != NULL) {
    aux = list->next;
    delete list;
    list = aux;
  }
}

Node * copyList(Node * list) {
  if (list == NULL) {
    return NULL;
  }
  List * nueva = new List, runnerOld = lista, runnerNew = nueva;
  runnerNew->data = runnerOld->data;
  while (runnerOld->next != NULL) {
    runnerNew->next = new List;
    runnerOld = runnerOld->next;
    runnerNew = runnerNew->next;
    runnerNew->data = runnerOld->data;
  }
  runnerNew->next = NULL;
  return nueva;
}

////////////////////////////////////////////////////////////////////////////////
struct Tree {
  int data;
  Tree * left;
  Tree * right;
};

void creatMinimalTree(int * array, int nums, Tree * &tree) {
  int mid = nums/2;
  tree->data = array[mid];
  if (nums == 1) {
    tree->left = NULL;
    tree->right = NULL;
  } else {
    tree->left = new Tree;
    creatMinimalTree(array, mid, tree->left);
    if (nums == 2) {
      tree->right = NULL;
    } else {
      tree->right = new Tree;
      creatMinimalTree(array+mid+1,
          nums%2 == 0 ? mid-1 : mid, tree->right);
    }
  }
}

void printTreeInOrder(Tree * tree) {
  if (tree != NULL) {
    printTreeInOrder(tree->left);
    cout << tree->data << " ";
    printTreeInOrder(tree->right);
  }
}

int treeDepth(Tree * tree, int depth_till_now) {
  if (tree == NULL) {
    return depth_till_now;
  }
  int rD = treeDepth(tree->right, depth_till_now+1),
      rL = treeDepth(tree->left, depth_till_now+1);
  return rD > rL ? rD : rL;
}

int treeDepth(Tree * tree) {
  return treeDepth(tree, 0);
}

void deleteTree(Tree * tree) {
  if (tree == NULL || (tree->right == NULL && tree->left == NULL)) {
    return;
  }
  deleteTree(tree->right);
  deleteTree(tree->left);
  if (tree->right != NULL) {
    delete tree->right;
  }
  if (tree->left != NULL) {
    delete tree->left;
  }
}

void BSTSequenceHelper() {
  
}

void BSTSequence(Tree * root) {
  if (root == NULL) {
    return;
  }

}


////////////////////////////////////////////////////////////////////////////////

int main () {
  Node * list = NULL;
  string str = "alocarac aloh";
  addString(list, str);
  print(list);
  deleteList(list);
}


int main() {
  int array[7], depth;
  for (int i=0; i<8; i++) array[i]=i;
  Tree * tree = new Tree;
  creatMinimalTree(array, 8, tree);

  cout << treeDepth(tree, 0) << endl;
  cout << "Tree: ";
  printTreeInOrder(tree);
  cout << endl;
  cout << "BST: " << isBinarySearchTree(tree) << endl;

  deleteTree(tree);
}
