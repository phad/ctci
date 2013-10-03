#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

// k is a 0-based index into the list;
// returns the first ('left') partition and sets
// second to point to the second ('right') partition.
node* partitionList(node* head, int k, node** second) {
  node* ptr = head;
  node* prev = NULL;
  while (ptr && k > 0) {
    prev = ptr;
    ptr = ptr->next;
    --k;
  }
  *second = ptr;
  node* first = head;
  if (prev) {
    prev->next = NULL;
  } else {
    first = NULL;
  }
  return first;
}

int main(int argc, char** argv) {
  const int LIST_SIZE = 8;
  int partIdx;
  for (partIdx = LIST_SIZE - 1; partIdx >= 0; --partIdx) {
    node *head = NULL, *prev = NULL;
    int count;
    for (count = 1; count <= LIST_SIZE; ++count) {
      node* n = add(count, prev);
      if (!head) {
        head = n;
      }
      prev = n;
    }

    printf("\nInitial linked list; partitioning at idx %d\n", partIdx);
    output(head);

    node* second = NULL;
    node* first = partitionList(head, partIdx, &second);
    printf("\nFirst partition\n");
    output(first);
    printf("\nSecond partition\n");
    output(second);

    release(first);
    release(second);
  }
  return 0;
}
