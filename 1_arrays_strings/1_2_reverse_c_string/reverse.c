#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char* reverse(const char* in) {
  if (!in) {
    return NULL;
  }
  size_t len = strlen(in);
  char* out = (char*) malloc(1 + len);  // 1 for NUL
  const char *iptr;
  char *optr;
  for (iptr = in + len - 1, optr = out; iptr >= in; ++optr, --iptr) {
    *optr = *iptr;
  }
  *optr = '\0';
  return out;
}

int main(int argc, char **argv) {
  char* reversed = reverse("Madam I'm Adam");
  printf("Reversed: %s\n", reversed);
  free(reversed);
  return 0;
}

