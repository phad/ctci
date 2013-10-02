#include <stdlib.h>

#include "../linked_list.h"

void remove_duplicates(node* root) {
  node* ptr = root;
  while (ptr) {
    int val = ptr->i;
    node* prev_check = ptr;
    node* check = ptr->next;
    while(check) {
      if (check->i == val) {
        discard(prev_check);
        check = prev_check;
      }
      prev_check = check;
      check = check->next;
    }
    ptr = ptr->next;
  }
}

int main(int argc, char** argv) {
  node* head = add(1, NULL);
  node* next = add(2, head);
  next = add(2, next);
  next = add(4, next);
  next = add(3, next);
  next = add(1, next);
  next = add(3, next);
  add(4, next);
  output(head);
  remove_duplicates(head);
  output(head);
  release(head);
  return 0;
}
