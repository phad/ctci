#include <assert.h>

int checkIfPower2(int value) {
  return (value & (value - 1)) == 0 ? 1 : 0;
}

int main(int argc, char **argv) {
  assert(checkIfPower2(1) == 1);
  assert(checkIfPower2(2) == 1);
  assert(checkIfPower2(3) == 0);
  assert(checkIfPower2(4) == 1);
  assert(checkIfPower2(7) == 0);
  assert(checkIfPower2(8) == 1);
  assert(checkIfPower2(15) == 0);
  assert(checkIfPower2(32) == 1);
  return 0;
}

