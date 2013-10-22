#include <assert.h>

typedef unsigned int uint32;

uint32 copy_substring(uint32 n, uint32 m, int i, int j) {
  assert(i >= 0 && i < 32);
  assert(j >= i && j <= 32);

  int mask_width = j - i + 1;
  uint32 mask = 0;
  while (mask_width-- > 0) {
    mask = 1 + (mask << 1);
  }

  mask <<= i;
  m <<= i;

  n &= (0xffffffff ^ mask);
  n |= m;
  return n;
}

int main(int argc, char **argv) {
  assert(copy_substring(0xff, 0xa, 3, 6) == 0xd7);
  assert(copy_substring(0x0f, 0xf, 4, 7) == 0xff);
  assert(copy_substring(0x0,  0x3, 3, 4) == 0x18);
  return 0;
}

