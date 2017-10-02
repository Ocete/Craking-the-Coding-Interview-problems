#include <iostream>
#include <cmath>
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

bool isBalanced (Tree * tree, int &depth) {
  if (tree == NULL) {
    return true;
  }
  int depthR = depth+1, depthL = depthR;
  bool rB = isBalanced(tree->right, depthR),
       rL = isBalanced(tree->left, depthL);
  depth = depthR > depthL ? depthR : depthL;
  cout << tree->data << " " << abs(depthR - depthL) << endl;
  return rB && rL && abs(depthR - depthL) <= 1;
}

bool isBalanced(Tree * tree) {
  if (tree == NULL) {
    return true;
  }
  int aux;
  return isBalanced(tree, aux);
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
  cout << "Balanced: " << isBalanced(tree) << endl;

  Tree * tree2 = new Tree;
  tree2->left = NULL;
  tree2->right = new Tree;
  tree2->right->left = NULL;
  tree2->right->right = new Tree;
  tree2->right->right->left = NULL;
  tree2->right->right->right = NULL;
  cout << "Balanced: " << isBalanced(tree2) << endl;

  deleteTree(tree);
  deleteTree(tree2);
}
