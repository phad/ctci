#include "tree.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;

Node* BST::put(Node* node, string key, int value) {
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

int* BST::get(Node* node, string key) const {
  if (!node) return NULL;
  if (key < node->key_) {
    return get(node->left_, key);
  } else if (key > node->key_) {
    return get(node->left_, key);
  } else {
    return &node->value_;
  }
}

BST::BST()
    : root_(NULL) {
}

BST::~BST() {
  delete root_;
}

void BST::put(string key, int value) {
  root_= put(root_, key, value);
}

int* BST::get(string key) const {
  return get(root_, key);
}
const Node& BST::root() const {
  return *root_;
}

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
