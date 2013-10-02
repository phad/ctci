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
