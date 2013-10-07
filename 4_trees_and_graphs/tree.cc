#include "tree.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;

Node* BST::put(Node* node, const Node* parent, string key, int value) {
  if (!node) {
    return new Node(key, value, parent);
  }
  if (key < node->key_) {
    node->left_ = put(node->left_, node, key, value);
  } else if (key > node->key_) {
    node->right_ = put(node->right_, node, key, value);
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
  root_= put(root_, NULL, key, value);
}

int* BST::get(string key) const {
  return get(root_, key);
}
const Node& BST::root() const {
  return *root_;
}

// Tree output inspired by:
// http://stackoverflow.com/questions/1649027/how-do-i-print-out-a-tree-structure
ostream& outputNode(ostream& ostr, const Node& node,
    string indent, bool isLeft, bool isLast) {
  ostr << indent;
  bool isRoot = indent.size() == 0;
  if (isLast) {
    ostr << "\\-";
    indent += "  ";
  } else {
    ostr << "|-";
    indent += "| ";
  }
  if (isRoot) {
    ostr << "o-";
  } else {
    ostr << (isLeft ? "<-" : ">-");
  }
  ostr << node.key_ << "(" << node.value_ << ")" << endl;
  if (node.left_) {
    outputNode(ostr, *node.left_, indent, true, (node.right_ == NULL));
  }
  if (node.right_) {
    outputNode(ostr, *node.right_, indent, false, true);
  }
  return ostr;
} 

ostream& operator<<(ostream& ostr, const BST& bst) {
  return outputNode(ostr, bst.root(), "" , false, true);
}
