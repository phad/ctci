#include <assert.h>

#include <iostream>
#include <string>
#include <vector>

#include "../tree.h"

using namespace std;

namespace {

int abs(int value) {
  return value < 0 ? -value : value;
}

}  // namespace

const Node& commonAncestor(const Node& first, const Node& second) {
  // measure height of path to root for both nodes.  root itself will have height 0
  int heightFirst = 0, heightSecond = 0;
  for (const Node* f = &first;  f->parent_ != NULL; f = f->parent_, heightFirst++) ;
  for (const Node* s = &second; s->parent_ != NULL; s = s->parent_, heightSecond++) ;

  // figure out which node has the shorter path to root, call it path2
  const Node* path1 = (heightFirst < heightSecond) ? &second : &first;
  const Node* path2 = (heightFirst < heightSecond) ? &first : &second;

  // skip over the deepest nodes in the longer path, this leaves us with two paths to
  // root of equal length.  the first common ancestor must be in this set.
  for (int i = 0; i < ::abs(heightFirst - heightSecond); ++i, path1 = path1->parent_) ;

  // finally iterate both paths until we hit the common node
  while (path1 != path2) {
    path1 = path1->parent_;
    path2 = path2->parent_;
  }

  return *path1;
}

int main(int argc, char **argv) {
  string kKeys[] = {"E", "C", "A", "D", "B", "G", "F", "H"};
  int kVals[] = {5, 3, 1, 4, 2, 7, 6, 8};

  BST* bst = new BST();
  for (int i = 0; i < sizeof(kVals) / sizeof(int); ++i) {
    bst->put(kKeys[i], kVals[i]);
  }
  cout << *bst << endl;

  assert(&commonAncestor(bst->root(), *bst->root().left_) == &bst->root());
  assert(&commonAncestor(*bst->root().right_, *bst->root().left_) == &bst->root());
  assert(&commonAncestor(*bst->root().right_->right_, *bst->root().right_->left_) == bst->root().right_);
  assert(&commonAncestor(*bst->root().left_->right_, *bst->root().right_->left_) == &bst->root());

  delete bst;
  return 0;
}
