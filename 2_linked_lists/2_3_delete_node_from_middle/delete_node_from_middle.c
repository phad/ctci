#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

// k is a 0-based index into the list;
// returns the new head of the list in case it is the
// current head that is deleted.
node* delete_kth_node(node* head, int k) {
  node* ptr = head;
  node* prev = NULL;
  while (ptr && k > 0) {
    prev = ptr;
    ptr = ptr->next;
    --k;
  }

  // Unlink 'ptr' if we didn't run off the end of the list.
  node* new_head = head;
  if (ptr) {
    if (prev) {
      prev->next = ptr->next;
    } else {
      new_head = ptr->next;
    }
    free(ptr);
  }

  return new_head;
}

int main(int argc, char** argv) {
  node* head = add(1, NULL);
  node* next = add(2, head);
  next = add(3, next);
  next = add(4, next);
  next = add(5, next);
  next = add(6, next);
  add(7, next);

  printf("\nInitial linked list\n");
  output(head);

  int j;
  for (j = 0; j < 2; ++j) {
    int k;
    for (k = 4; k >= 0; --k) {
      printf("\nDeleting %dth element\n", k);
      head = delete_kth_node(head, k);
      output(head);
    }
  }

  release(head);
  return 0;
}
