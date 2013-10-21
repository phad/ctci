#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../tree.h"

using namespace std;

const Node* leftmostDescendant(const Node* node) {
  while(node->left_) {
    node = node->left_;
  }
  return node;
}

const Node* rightmostAncestor(const Node* node) {
  while (node->parent_ && node != node->parent_->left_) {
    node = node->parent_;
  }
  return node->parent_;
}

const Node* inOrderSuccessor(const Node* node) {
  if (node->left_ == NULL && node->right_ == NULL) {
    if (!node->parent_) {
      return NULL;
    }
    if (node == node->parent_->left_) {
      return node->parent_;
    } else {  // node == node->parent_->right_
      // traverse up through parents until we find we're the left child
      return rightmostAncestor(node->parent_);      
    }
  } else if (node->right_) {
    return leftmostDescendant(node->right_);
  } else {  // moving to node->left_ won't occur in in-order iteration.
    return NULL;
  }
}

int main(int argc, char** argv) {
  BST* tree = new BST;
  int vals[] = {18, 14, 12, 13, 16, 15, 17, 22, 20, 19, 21, 24, 25};
  for (int idx = 0; idx < sizeof(vals)/sizeof(int); ++idx) {
    ostringstream oss;
    oss << vals[idx];
    tree->put(oss.str(), vals[idx]);
  }
  cout << *tree << endl;

  const Node* start = leftmostDescendant(&tree->root());
  while(start) {
    cout << start->value_ << ", ";
    start = inOrderSuccessor(start);
  }
  cout << endl;

  delete tree;
  return 0;
}

