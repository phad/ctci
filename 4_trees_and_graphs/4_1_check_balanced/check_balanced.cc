#include <assert.h>

#include <iostream>
#include <string>

using namespace std;

class Node {
 public:
  Node(string key, int value)
      : key_(key), value_(value),
        left_(NULL), right_(NULL) {}
  ~Node() { delete left_; delete right_; }

  string key_;
  int value_;
  Node* left_;
  Node* right_;
};

class BST {
 private:
  BST(const BST&);
  BST& operator=(const BST&);

  Node* put(Node* node, string key, int value) {
    if (!node) {
      return new Node(key, value);
    }
    if (key < node->key_) {
      node->left_ = put(node->left_, key, value);
    } else if (key > node->key_) {
      node->right_ = put(node->right_, key, value);
    } else {
      node->value_ = value;
    }
    return node;
  }

  int* get(Node* node, string key) const {
    if (!node) return NULL;
    if (key < node->key_) {
      return get(node->left_, key);
    } else if (key > node->key_) {
      return get(node->left_, key);
    } else {
      return &node->value_;
    }
  }

  Node* root_;
  friend ostream& operator<<(ostream& ostr, const BST& bst);

 public:
  BST() : root_(NULL) { }
  ~BST() { delete root_; }

  void put(string key, int value) {
    root_= put(root_, key, value);
  }
  int* get(string key) const {
    return get(root_, key);
  }
  const Node& root() const { return *root_; }
};

ostream& outputNode(ostream&ostr, const Node& node, int depth) {
  string indent;
  for (int d = 0; d < depth; ++d) { indent += ' '; }
  ostr << indent << "K: " << node.key_ << " V: " << node.value_ << endl;
  if (node.left_) {
    ostr << indent << "L:" << endl;
    outputNode(ostr, *node.left_, depth + 1);
  }
  if (node.right_) {
    ostr << indent << "R:" << endl;
    outputNode(ostr, *node.right_, depth + 1);
  }
  return ostr;
}

ostream& operator<<(ostream& ostr, const BST& bst) {
  return outputNode(ostr, bst.root(), 0);
}

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