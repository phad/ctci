#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct _node {
  int i;
  struct _node* next;
} node;

node* add(int v, node* prev);
void discard(node* prev);
void release(node* head);
void output(node* n);
node* reverse(node* head);
node* duplicate(node* head);

#endif
