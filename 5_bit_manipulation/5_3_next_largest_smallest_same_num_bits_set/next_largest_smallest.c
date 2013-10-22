#include <assert.h>
#include <stdio.h>

int numBitsSet(int value) {
  int count = 0;
  while (value > 0) {
    value &= (value - 1);
    ++count;
  }
  return count;
}

int nextLargest(int value) {
  assert(value > 0);
  int origNumSet = numBitsSet(value);
  do {
    ++value;
  } while (numBitsSet(value) != origNumSet);
  return value;
}

int nextSmallest(int value) {
  /* there is no next-smallest for 0001, 0011, 0111 etc. */
  assert((value & (value + 1)) != 0); 
  int origNumSet = numBitsSet(value);
  do {
    --value;
  } while (numBitsSet(value) != origNumSet);
  return value;
}

int main(int argc, char** argv) {
  int i;
  for (i = 1; i < 33; ++i) {
    if ((i & (i + 1)) == 0) {
      printf("     %d -> %d  (no next smallest for %d)\n", i, nextLargest(i), i);
    } else {
      printf("%d <- %d -> %d\n", nextSmallest(i), i, nextLargest(i));
    }
  }
  return 0;
}

