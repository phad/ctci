#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned short uint8;

const uint8 REPEAT_START  = 0x80;

typedef enum {
  EInLiteral = 0,
  EInRepeat = 1
} State;

char* compressString(const char* in) {
  char* out = (char*) malloc(1 + strlen(in));
  memset(out, 0, 1 + strlen(in));

  State state = EInLiteral;
  int repeatCount = 0;
  const char* iptr = in;
  char previous = '\0';

  char* optr = out;
  int lastTagIndex = -1;

  while (*iptr) {
    if (*iptr == previous) {
      switch(state) {
        case EInLiteral:
          state = EInRepeat;
          // Back over previous char so we can count it in
          // the repeat.
          --optr;
          lastTagIndex = optr - out;
          *optr++ = REPEAT_START;
          *optr++ = *iptr;
          repeatCount = 2;
          break;
        case EInRepeat:
          ++repeatCount;
          break;
      }
    } else {
      switch(state) {
        case EInLiteral:
          break;
        case EInRepeat:
          *(out + lastTagIndex) += repeatCount;
          state = EInLiteral;
          repeatCount = 0;
          break;
      }
      *optr++ = *iptr;
    }
    previous = *iptr++;
  }
  // Finally update last tag if in repeat
  if (state == EInRepeat) {
    *(out + lastTagIndex) +=  repeatCount;
  }

  return out;
}

void test(const char* input, const char* expectedCompressed) {
  char* compressed = compressString(input);
  if (strcmp(compressed, expectedCompressed) == 0) {
    printf("PASS: orig len %lu; compressed len %lu\n", strlen(input), strlen(compressed));
  } else {
    printf("FAIL: got %s; expected %s\n", compressed, expectedCompressed);
  }
  free(compressed);
}

int main(int argc, char **argv) {
  test("paul", "paul");
  test("hello", "he\x82lo");
  test("aaaa", "\x84""a");
  test("bbbbbbbb", "\x88""b");
  test("oppqqqrrrrssssstuuuuvvvww",
     "o\x82p\x83q\x84r\x85st\x84u\x83v\x82w");
  return 0;
}