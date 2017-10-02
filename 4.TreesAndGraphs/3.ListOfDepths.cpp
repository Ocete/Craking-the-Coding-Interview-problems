#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
struct ListNode {
  int data;
  ListNode * next;
};

int charAt (char c) {
  int dif = c - 'a';
  return (dif >= 0 && dif < 128) ? dif : -1;
}

void add (ListNode * &list, int i) {
  ListNode * nuevo = new ListNode;
  nuevo->data = i;
  nuevo->next = list;
  list = nuevo;
}

void printList (ListNode * list) {
  ListNode * aux = list;
  while (aux != NULL) {
    cout << aux->data << " ";
    aux = aux->next;
  }
  cout << endl;
}

void deleteList (ListNode * list) {
  ListNode * aux = list;
  while (list != NULL) {
    aux = list->next;
    delete list;
    list = aux;
  }
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

int treeDepth(Tree * tree) {
  return treeDepth(tree, 0);
}

void addToListOfDepths(Tree * tree, int depth, ListNode ** ListsArray) {
  if (tree == NULL) {
    return;
  }
  add(ListsArray[depth], tree->data);
  addToListOfDepths(tree->left, depth+1, ListsArray);
  addToListOfDepths(tree->right, depth+1, ListsArray);
}

ListNode ** listOfDepths(Tree * tree, int &depth) {
  if (tree == NULL) {
    return NULL;
  }
  depth = treeDepth(tree);
  ListNode ** ListsArray = new ListNode*[depth];
  for (int i=0; i<depth; i++) {
    ListsArray[i] = NULL;
  }
  addToListOfDepths(tree, 0, ListsArray);
  return ListsArray;
}

int main() {
  int array[8], depth;
  for (int i=0; i<8; i++) array[i]=i;
  Tree * tree = new Tree;
  creatMinimalTree(array, 8, tree);

  cout << treeDepth(tree, 0) << endl;
  cout << "Tree: ";
  printTreeInOrder(tree);
  cout << endl;

  ListNode ** ListsArray = listOfDepths(tree, depth);
  for (int i=0; i<depth; i++) {
    cout << "Depth = " << i << ":" << endl;
    printList(ListsArray[i]);
  }

  deleteTree(tree);
}
