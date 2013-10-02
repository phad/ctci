#include <stdlib.h>

#include "../linked_list.h"

node* reverse(node* root) {
  node* new_root = 0;
  while (root) {
    node* next = root->next;
    root->next = new_root;
    new_root = root;
    output(new_root);
    root = next;
    output(root);
  }
  return new_root;
}

int main(int argc, char** argv) {
  node* head = add(1, NULL);
  node* next = add(2, head);
  next = add(3, next);
  add(4, next);
  output(head);
  node* reversed = reverse(head);
  output(reversed);
  release(reversed);
  return 0;
}
