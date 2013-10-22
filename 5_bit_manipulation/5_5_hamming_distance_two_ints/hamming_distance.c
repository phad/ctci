#include <assert.h>

int hammingDistance(int a, int b) {
  int c = a ^ b;
  int r = 0;
  while (c) {
    c &= c - 1;
    r++;
  }
  return r;
}

int main(int argc, char **argv) {
  assert(hammingDistance(2, 1) == 2);
  assert(hammingDistance(255, 0) == 8);
  assert(hammingDistance(240, 15) == 8);
  assert(hammingDistance(15, 16) == 5);
  assert(hammingDistance(123, 123) == 0);
  return 0;
}

