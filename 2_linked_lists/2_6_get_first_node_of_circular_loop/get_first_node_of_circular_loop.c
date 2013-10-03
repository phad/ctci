#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

node* detectLoop(node* head) {
  node *a = head, *b = head;
  while (a->next && b->next && b->next->next) {
    a = a->next;
    b = b->next->next;
    if (a == b) {
      break;
    }
  }
  return (a == b) ? a->next : NULL;
}

int main(int argc, char** argv) {
  node* headNoLoop = add(1, NULL);
  node* next = add(2, headNoLoop);
  next = add(3, next);
  next = add(4, next);
  next = add(5, next);
  add(6, next);

  node* headWithLoop = add(1, NULL);
  next = add(2, headWithLoop);
  next = add(3, next);
  next = add(4, next);
  node* looped = next;
  next = add(5, next);
  next = add(6, next);
  next->next = looped;

  printf("\nLinked list, no loop\n");
  output(headNoLoop);

  node* firstLooped = detectLoop(headNoLoop);
  printf("\nLoop detected? %d\n", firstLooped != NULL);
  assert(firstLooped == NULL);

  printf("\nLinked list, has loop\n");
  // output(headWithLoop);  infinite loop right now

  firstLooped = detectLoop(headWithLoop);
  printf("\nLoop detected? %d\n", firstLooped != NULL);
  printf("Value at loop node: %d\n", firstLooped->i);
  assert(firstLooped == looped);

  release(headNoLoop);
  // release(headWithLoop);  infinite loop right now
  return 0;
}
