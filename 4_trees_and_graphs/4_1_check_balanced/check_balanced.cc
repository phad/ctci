#include <assert.h>

#include <iostream>
#include <string>

#include "../tree.h"

using namespace std;

bool isBalanced(const Node& n) {
  if (n.left_ && n.right_) {
    return isBalanced(*n.left_) && isBalanced(*n.right_);
  } else if (n.left_ && !n.right_) {
    return (n.left_->left_ == NULL) && (n.left_->right_ == NULL); 
  } else if (!n.left_ && n.right_) {
    return (n.right_->left_ == NULL) && (n.right_->right_ == NULL); 
  }
  return true;
}

void testTree(string* keys, int* values, int count, bool expBal) {
  BST* bst = new BST();
  for (int i = 0; i < count; ++i) {
    bst->put(keys[i], values[i]);
  }
  cout << *bst << endl;
  bool bal = isBalanced(bst->root());
  cout << "Balanced? " << bal << endl << endl;
  delete bst;
  assert(bal == expBal);
}

int main(int argc, char **argv) {
  string kKeys1[] = {"C", "A", "D", "B", "E", "F"};
  int kVals1[] = {3, 1, 4, 2, 5, 6};
  testTree(kKeys1, kVals1, sizeof(kVals1) / sizeof(int), false);

  string kKeys2[] = {"A"};
  int kVals2[] = {1};
  testTree(kKeys2, kVals2, sizeof(kVals2) / sizeof(int), true);

  string kKeys3[] = {"B", "A"};
  int kVals3[] = {2, 1};
  testTree(kKeys3, kVals3, sizeof(kVals3) / sizeof(int), true);

  string kKeys4[] = {"B", "A", "C"};
  int kVals4[] = {2, 1, 3};
  testTree(kKeys4, kVals4, sizeof(kVals4) / sizeof(int), true);

  string kKeys5[] = {"B", "A", "C", "D"};
  int kVals5[] = {2, 1, 3, 4};
  testTree(kKeys5, kVals5, sizeof(kVals5) / sizeof(int), true);

  string kKeys6[] = {"B", "A", "C", "D", "E"};
  int kVals6[] = {2, 1, 3, 4, 5};
  testTree(kKeys6, kVals6, sizeof(kVals6) / sizeof(int), false);

  return 0;
}