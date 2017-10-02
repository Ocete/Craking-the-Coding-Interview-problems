#include <iostream>
#include <limits>
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

////////////////////////////////////////////////////////////////////////////////
/*
bool DFS(Tree * start, Tree * searching) {
  if (start == NULL) {
    return false;
  } else if (start == searching) {
    return true;
  }
  //cout << start->data << " " << searching->data << endl;
  return DFS(start->right, searching) || DFS(start->left, searching);
}

Tree * DirectChild(Tree * node1, Tree * node2) {
  if (DFS(node1, node2)) {
    return node1;
  } else if (DFS(node2, node1)) {
    return node2;
  } else {
    return NULL;
  }
}

Tree * NotDirectChild(Tree * node1, Tree * node2) {
  Tree * aux = node1;
  bool found = false;
  while (!found && aux->parent != NULL) {
    found = DFS(aux == aux->parent->left ? aux->parent->right : aux->parent->left, node2);
    aux = aux->parent;
  }
  return found ? aux : NULL;
}

Tree * firstCommonAncestor(Tree * node1, Tree * node2) {
  if (node1 == NULL || node2 == NULL) {
    return NULL;
  }
  Tree * ancestor = DirectChild(node1, node2);
  if (ancestor != NULL) {
    return ancestor;
  }
  ancestor = NotDirectChild(node1, node2);
  return ancestor;
}
*/
////////////////////////////////////////////////////////////////////////////////

Tree * Ancestor(Tree * root, Tree * node1, Tree * node2, bool &rootB) {
  if (root == NULL) {
    rootB = false;
    return NULL;
  }
  bool left, right;
  Tree * ancestor;
  ancestor = Ancestor(root->left, node1, node2, left);
  if (ancestor != NULL) {
    return ancestor;
  }
  ancestor = Ancestor(root->right, node1, node2, right);
  if (ancestor != NULL) {
    return ancestor;
  }
  rootB = root == node1 || root == node2;
  // Remember: && before ||
  if (left && right || rootB && (left || right)) {
    return root;
  }
  rootB = rootB || left || right;
  return NULL;
}

Tree * firstCommonAncestor(Tree * root, Tree * node1, Tree * node2) {
  if (node1 == NULL || node2 == NULL) {
    return NULL;
  }
  bool B;
  return Ancestor(root, node1, node2, B);
}

int main() {
  int array[16], depth;
  for (int i=0; i<16; i++) array[i]=i;
  Tree * tree = new Tree;
  creatMinimalTree(array, 16, tree);
  printTreeInOrder(tree);
  cout << endl;
  Tree * ancestor = firstCommonAncestor(tree, tree->left->left->right, tree), *NF = new Tree;
  cout << "First Common Ancestor of 3 and 8: " << ancestor->data << endl;
  ancestor = firstCommonAncestor(tree, tree->right, tree->right->left->right);
  cout << "First Common Ancestor of 12 and 11: " << ancestor->data << endl;
  ancestor = firstCommonAncestor(tree, tree->left->left->right, tree->left->right->right);
  cout << "First Common Ancestor of 3 and 7: " << ancestor->data << endl;
  ancestor = firstCommonAncestor(tree, tree->right->right->left, tree->left->right->left);
  cout << "First Common Ancestor of 13 and 5: " << ancestor->data << endl;
  NF->right = NF->left = NF->parent = NULL;
  ancestor = firstCommonAncestor(tree, tree->right->right->left, NF);
  bool b = ancestor != NULL;
  cout << "First Common Ancestor of 13 and NOT FOUND: " << b << endl;
  deleteTree(tree);
}
