#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

node* add(int v, node* prev) {
  node* n = malloc(sizeof(node));
  n->i = v;
  n->next = NULL;
  if (prev) {
    prev->next = n;
  }
  return n;
}

void discard(node* prev) {
  node* to_remove = prev->next;
  if (to_remove) {
    prev->next = to_remove->next;
    free(to_remove);
  }
}

void release(node* head) {
  node* next = NULL;
  while (head) {
    next = head->next;
    free(head);
    head = next;
  }
}

void output(node* n) {
  printf("HEAD: ");
  while (n) {
    printf("%d -> ", n->i);
    n = n->next;
  }
  printf("NULL\n");
}
