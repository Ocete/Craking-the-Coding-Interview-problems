#include <iostream>
using namespace std;

/*  WARNING
  This whole program uses a diferent struct Tree than others (it has a parent)
  Every function has been changed accordingly
*/

struct Tree {
  int data;
  Tree * left;
  Tree * right;
  Tree * parent;
};

void creatMinimalTree(int * array, int nums, Tree * &tree, Tree * parent) {
  int mid = nums/2;
  tree->data = array[mid];
  tree->parent = parent;
  if (nums == 1) {
    tree->left = NULL;
    tree->right = NULL;
  } else {
    tree->left = new Tree;
    creatMinimalTree(array, mid, tree->left, tree);
    if (nums == 2) {
      tree->right = NULL;
    } else {
      tree->right = new Tree;
      creatMinimalTree(array+mid+1,
          nums%2 == 0 ? mid-1 : mid, tree->right, tree);
    }
  }
}

void creatMinimalTree(int * array, int nums, Tree * &tree) {
  creatMinimalTree(array, nums, tree, NULL);
}


void printTreeInOrder(Tree * tree) {
  if (tree != NULL) {
    printTreeInOrder(tree->left);
    cout << tree->data << " ";
    printTreeInOrder(tree->right);
  }
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

// Returns NULL if there is no successor
Tree * successor(Tree * start) {
  if (start == NULL) {
    return NULL;
  }
  Tree * successor, *aux = start->right == NULL ? NULL : start->right;
  if (aux != NULL) {
    while (aux->left != NULL) {
      aux = aux->left;
    }
    successor = aux;
  } else {
    aux = start;
    while (aux->parent != NULL && aux->parent->left != aux) {
      aux = aux->parent;
    }
    successor = aux->parent;
  }
  return successor == start ? NULL : successor;
}

int main() {
  int array[16], depth;
  for (int i=0; i<16; i++) array[i]=i;
  Tree * tree = new Tree;
  creatMinimalTree(array, 16, tree);
  bool B;
  cout << "Tree: ";
  printTreeInOrder(tree);
  cout << endl;
  Tree * aux = tree->right->left, *suc = successor(aux);
  cout << "Node: " << aux->data << endl << "successor: " << suc->data << endl;
  aux = tree->right->right->right, suc = successor(aux), B = suc == NULL;
  cout << "Node: " << aux->data << endl << "successor is NULL: " << B << endl;
  aux = tree->left, suc = successor(aux);
  cout << "Node: " << aux->data << endl << "successor: " << suc->data << endl;
  aux = tree->left->right->right, suc = successor(aux);
  cout << "Node: " << aux->data << endl << "successor: " << suc->data << endl;

  deleteTree(tree);
}
