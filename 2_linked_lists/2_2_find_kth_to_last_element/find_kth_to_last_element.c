#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

node* find_kth_last(node* head, int j) {
  // Make circular buffer size k + 1 - we need one extra slot.
  int k = j + 1;
  assert(k > 0);
  node** circBuf = (node**) malloc(k * sizeof(node*));
  memset(circBuf, 0, k * sizeof(node*));
  int cbHeadIdx = 0;
  int cbTailIdx = 0;

  // Traverse list, popularing circBuf, until we hit terminator.
  node* ptr = head;
  while (ptr) {
    circBuf[cbHeadIdx] = ptr;
    cbHeadIdx = (cbHeadIdx + 1) % k;
    if (cbHeadIdx == cbTailIdx) {
      cbTailIdx = (cbTailIdx + 1) % k;
    }
    ptr = ptr->next;
  }

  // At terminator, the kth-last element is pointed to by the circular buffer
  // element 1 step ahead of the head pointer.
  int resultIdx = (cbHeadIdx + 1) % k;
  node* result = circBuf[resultIdx];
  free(circBuf);
  return result;
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

  int k;
  for (k = 1; k <= 9; ++k) {
    printf("\nFinding %dth-to-last element\n", k);
    node* kthLast = find_kth_last(head, k);
    output(kthLast);
  }

  release(head);
  return 0;
}
