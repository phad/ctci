#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

int isIdentical(node* head1, node* head2) {
  node *ptr1 = head1, *ptr2 = head2;
  int result = 1;
  while (ptr1 != NULL && ptr2 != NULL) {
    if (ptr1->i != ptr2->i) {
      result = 0;
      break;
    }
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
  return result;
}

int isPalindrome(node* head) {
  node* headCopy = duplicate(head);
  node* reversedHead = reverse(headCopy);
  int result = isIdentical(head, reversedHead);
  release(reversedHead);
  return result;
}

int main(int argc, char** argv) {
  node* headNotPalin = add(1, NULL);
  node* next = add(2, headNotPalin);
  next = add(3, next);
  next = add(4, next);
  next = add(5, next);
  add(6, next);

  node* headIsPalin = add(1, NULL);
  next = add(2, headIsPalin);
  next = add(3, next);
  next = add(4, next);
  next = add(3, next);
  next = add(2, next);
  add(1, next);

  printf("\nLinked list, not palindrome\n");
  output(headNotPalin);

  int isPalin =isPalindrome(headNotPalin);
  printf("\nIs palindrome? %d\n", isPalin);
  assert(isPalin == 0);

  printf("\nLinked list, is palindrome\n");
  output(headIsPalin);

  isPalin = isPalindrome(headIsPalin);
  printf("\nIs palindrome? %d\n", isPalin);
  assert(isPalin == 1);

  release(headNotPalin);
  release(headIsPalin);
  return 0;
}
