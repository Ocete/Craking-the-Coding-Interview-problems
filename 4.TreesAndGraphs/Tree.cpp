#include <iostream>
using namespace std;

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

int main() {
  int array[8];
  for (int i=0; i<8; i++) array[i]=i;
  Tree * tree = new Tree;
  creatMinimalTree(array, 8, tree);
  printTreeInOrder(tree);
  cout << endl;
  delete(tree);
}
