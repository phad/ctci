#include <assert.h>

typedef unsigned int uint32;

uint32 swapOddEven(uint32 value) {
  return ((value & 0xaaaaaaaa) >> 1) | ((value & 0x55555555) << 1);
}

int main(int argc, char **argv) {
  assert(swapOddEven(0x0) == 0x0);
  assert(swapOddEven(0x5) == 0xa);
  assert(swapOddEven(0x8) == 0x4);
  assert(swapOddEven(0x21212121) == 0x12121212);
  return 0;
}

