#include <assert.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "../tree.h"

using namespace std;

void insert(BST* tree, const vector<int>& values, int lo, int hi) {
  int mid = (lo + hi) / 2;
  int midVal = values[mid];
  ostringstream oss;
  oss << char(65 + mid);
  tree->put(oss.str(), midVal);
  if (hi > lo + 1) {
    insert(tree, values, lo, mid);
    insert(tree, values, mid + 1, hi);
  }
}

BST* createBalancedBST(const vector<int>& values) {
  vector<int> sortedValues(values);
  sort(sortedValues.begin(), sortedValues.end());

  BST* bst = new BST();
  insert(bst, sortedValues, 0, sortedValues.size());  
  return bst;
}

int main(int argc, char **argv) {
  int kVals[] = {5, 13, 1, 4, 12, 7, 6, 8, 3, 10, 11, 2, 9, 15, 14};
  vector<int> values(kVals, kVals + sizeof(kVals) / sizeof(int));

  BST* bst = createBalancedBST(values);
  cout << *bst << endl;

  assert(bst->isBalanced());

  delete bst;
  return 0;
}