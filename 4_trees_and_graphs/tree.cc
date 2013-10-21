#include "tree.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;

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

int abs(int val) {
  return val < 0 ? -val : val;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int checkHeights(const Node* node) {
  if (node == NULL) {
    return 0;
  }
  int leftHeight = checkHeights(node->left_);
  if (leftHeight == -1) {
    return -1;
  }
  int rightHeight = checkHeights(node->right_);
  if (rightHeight == -1) {
    return -1;
  }
  if (abs(leftHeight - rightHeight) > 1) {
    return -1;
  }
  return 1 + max(leftHeight, rightHeight);
}

bool BST::isBalanced() const {
  return (checkHeights(root_) != -1);
}

typedef void (*TraversalFunctor)(const Node*, void*);

void inOrderTraversal(const Node* node, TraversalFunctor action, void* arg) {
  if (node->left_) inOrderTraversal(node->left_, action, arg);
  (*action)(node, arg);
  if (node->right_) inOrderTraversal(node->right_, action, arg);
}

void preOrderTraversal(const Node* node, TraversalFunctor action, void* arg) {
  (*action)(node, arg);
  if (node->left_) preOrderTraversal(node->left_, action, arg);
  if (node->right_) preOrderTraversal(node->right_, action, arg);
}

void postOrderTraversal(const Node* node, TraversalFunctor action, void* arg) {
  if (node->left_) postOrderTraversal(node->left_, action, arg);
  if (node->right_) postOrderTraversal(node->right_, action, arg);
  (*action)(node, arg);
}

void addKeyToVector(const Node* node, void* arg) {
  vector<string>* keys = reinterpret_cast<vector<string>*>(arg);
  keys->push_back(node->key_);
}

vector<string> BST::keysTraversedInOrder() const {
  vector<string> keys;
  inOrderTraversal(root_, &addKeyToVector, reinterpret_cast<void*>(&keys));
  return keys;
}

vector<string> BST::keysTraversedPreOrder() const {
  vector<string> keys;
  preOrderTraversal(root_, &addKeyToVector, reinterpret_cast<void*>(&keys));
  return keys;
}

vector<string> BST::keysTraversedPostOrder() const {
  vector<string> keys;
  postOrderTraversal(root_, &addKeyToVector, reinterpret_cast<void*>(&keys));
  return keys;
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
