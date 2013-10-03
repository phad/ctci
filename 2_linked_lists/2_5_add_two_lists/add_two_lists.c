#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

// k is a 0-based index into the list;
// returns the new head of the list in case it is the
// current head that is deleted.
node* add_two_lists(node* head1, node* head2) {
  if (head1) {
    node* ptr = head1;
    while (ptr && ptr->next) {
      ptr = ptr->next;
    }
    ptr->next = head2;
  } else {
    head1 = head2;
  }
  // Unlink 'ptr' if we didn't run off the end of the list.
  node* new_head = (head1 ? head1 : (head2 ? head2 : NULL));
  return new_head;
}

int main(int argc, char** argv) {
  node* head1 = add(1, NULL);
  node* next = add(2, head1);
  add(3, next);

  node* head2 = add(4, NULL);
  next = add(5, head2);
  next = add(6, next);
  add(7, next);

  printf("\nInitial linked list, A\n");
  output(head1);

  printf("\nInitial linked list, B\n");
  output(head2);

  node* head = add_two_lists(head1, head2);

  printf("\nResult of adding lists A and B\n");
  output(head);

  release(head);
  return 0;
}
