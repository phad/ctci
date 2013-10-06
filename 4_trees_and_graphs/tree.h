#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

class Node {
 public:
  Node(std::string key, int value)
      : key_(key), value_(value),
        left_(NULL), right_(NULL) {}
  ~Node() { delete left_; delete right_; }

  std::string key_;
  int value_;
  Node* left_;
  Node* right_;
};

class BST {
 private:
  BST(const BST&);
  BST& operator=(const BST&);

  Node* put(Node* node, std::string key, int value);
  int* get(Node* node, std::string key) const;
  Node* root_;
  friend std::ostream& operator<<(std::ostream& ostr, const BST& bst);

 public:
  BST();
  ~BST();

  void put(std::string key, int value);
  int* get(std::string key) const;
  const Node& root() const;
};

std::ostream& operator<<(std::ostream& ostr, const BST& bst);

#endif