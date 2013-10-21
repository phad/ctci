#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../tree.h"

using namespace std;

void testKeyOrderMatchesExpected(const vector<string>& keys, const vector<int>& expected) {
  assert(keys.size() == expected.size());
  vector<string>::const_iterator it = keys.begin();
  vector<int>::const_iterator expIt = expected.begin();
  for(; it != keys.end(); ++it, ++expIt) {
    cout << *it << ", ";
    ostringstream oss;
    oss << *expIt;
    assert(*it == oss.str());
  }
  cout << endl;
}

int main(int argc, char** argv) {
  BST* tree = new BST;
  int vals[] = {4, 2, 1, 3, 6, 5, 7};
  for (int idx = 0; idx < sizeof(vals)/sizeof(int); ++idx) {
    ostringstream oss;
    oss << vals[idx];
    tree->put(oss.str(), vals[idx]);
  }
  cout << *tree << endl;

  // in-order traversal
  vector<string> inOrderKeys = tree->keysTraversedInOrder();
  int inOrderExpected[] = { 1, 2, 3, 4, 5, 6, 7 };
  testKeyOrderMatchesExpected(inOrderKeys, vector<int>(inOrderExpected, inOrderExpected + 7));

  // pre-order traversal
  vector<string> preOrderKeys = tree->keysTraversedPreOrder();
  int preOrderExpected[] = { 4, 2, 1, 3, 6, 5, 7 };
  testKeyOrderMatchesExpected(preOrderKeys, vector<int>(preOrderExpected, preOrderExpected + 7));

  // post-order traversal
  vector<string> postOrderKeys = tree->keysTraversedPostOrder();
  int postOrderExpected[] = { 1, 3, 2, 5, 7, 6, 4 };
  testKeyOrderMatchesExpected(postOrderKeys, vector<int>(postOrderExpected, postOrderExpected + 7));

  delete tree;
  return 0;
}

