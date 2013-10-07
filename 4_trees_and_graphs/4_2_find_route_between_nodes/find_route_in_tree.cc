#include <assert.h>

#include <iostream>
#include <string>
#include <vector>

#include "../tree.h"

using namespace std;

int shortestRoute(const Node& first, const Node& second) {
  vector<const Node*> rootToFirst, rootToSecond;
  for (const Node* fn = &first; fn != NULL; fn = fn->parent_) {
    rootToFirst.push_back(fn);
  }
  for (const Node* sn = &second; sn != NULL; sn = sn->parent_) {
    rootToSecond.push_back(sn);
  }
  while (true) {
    int sf = rootToFirst.size();
    int ss = rootToSecond.size();
    if ((sf <= 1) || (ss <= 1))
      break;
    if (rootToFirst[sf - 1] != rootToSecond[ss - 1])
      break;
    if (rootToFirst[sf - 2] != rootToSecond[ss - 2])
      break;
    rootToFirst.pop_back();
    rootToSecond.pop_back();
  }
  return rootToFirst.size() + rootToSecond.size() - 2;
}

int main(int argc, char **argv) {
  string kKeys[] = {"E", "C", "A", "D", "B", "G", "F", "H"};
  int kVals[] = {5, 3, 1, 4, 2, 7, 6, 8};

  BST* bst = new BST();
  for (int i = 0; i < sizeof(kVals) / sizeof(int); ++i) {
    bst->put(kKeys[i], kVals[i]);
  }
  cout << *bst << endl;

  assert(shortestRoute(bst->root(), bst->root()) == 0);
  assert(shortestRoute(bst->root(), *bst->root().left_) == 1);
  assert(shortestRoute(*bst->root().right_, *bst->root().left_) == 2);
  assert(shortestRoute(*bst->root().right_->right_, *bst->root().left_->left_) == 4);
  assert(shortestRoute(*bst->root().left_->right_, *bst->root().left_->left_) == 2);

  delete bst;
  return 0;
}