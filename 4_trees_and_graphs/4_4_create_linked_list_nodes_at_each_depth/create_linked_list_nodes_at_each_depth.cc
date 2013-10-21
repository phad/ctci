#include <iostream>
#include <sstream>
#include <vector>
#include "../tree.h"

using namespace std;

struct ListElement {
  const Node* node;
  ListElement* next;
  ListElement(const Node* n) : node(n), next(NULL) {}
};

void add(const Node* val, ListElement*& head, ListElement*& prev) {
  ListElement* elem = new ListElement(val);
  if (!head) {
    head = elem;
  }
  if (prev) {
    prev->next = elem;
  }
  prev = elem;
}

vector<ListElement*> bfsTreeAsLists(const BST& bst) {
  vector<ListElement*> result;
  // Seed with root
  result.push_back( new ListElement(&bst.root()) );
  bool done = false;
  ListElement* prevLevel = result.back();
  while(!done) {
    ListElement* head = NULL;
    ListElement* prev = NULL;
    while(prevLevel) {
      ListElement* elem = NULL;
      if (prevLevel->node->left_) {
        add(prevLevel->node->left_, head, prev);
      }
      if (prevLevel->node->right_) {
        add(prevLevel->node->right_, head, prev);
      }
      prevLevel = prevLevel->next;
    }
    if (head) {
      result.push_back(head);
      prevLevel = head;
    } else {
      done = true;
    }
  }
  return result;
}


int main(int argc, char** argv) {
  BST* tree = new BST;
  int vals[] = {0, 4, 2, 1, 3, 6, 5, 7, 8, 9};
  for (int idx = 0; idx < sizeof(vals)/sizeof(int); ++idx) {
    ostringstream oss;
    oss << vals[idx];
    tree->put(oss.str(), vals[idx]);
  }
  cout << *tree << endl;

  vector<ListElement*> lists = bfsTreeAsLists(*tree);
  for (vector<ListElement*>::iterator it = lists.begin(); it != lists.end(); ++it) {
    ListElement* head = *it;
    while(head) {
      cout << head->node->value_ << ",";
      ListElement* next = head->next;
      delete head;
      head = next;
    }
    cout << endl;
  }

  delete tree;
  return 0;
}

