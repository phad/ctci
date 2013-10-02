#include <stdio.h>
#include <stdlib.h>

char* replaceSpaces(const char* in) {
	if (!in) return NULL;
	int count = 0;
	const char* iptr = in;
	while (*iptr) {
		if (*iptr == ' ')
			++count;
		++iptr;
	}
	if (count == 0) {
		return strdup(in);
	}
	char* out = (char*) malloc(strlen(in) + 2 * count);
	iptr = in;
	char* optr = out;
	while (*iptr) {
		if (*iptr == ' ') {
			*optr++ = '%';
			*optr++ = '2';
			*optr++ = '0';
		} else {
			*optr++ = *iptr;
		}
		++iptr;
	}
	*optr = '\0';
	return out;
}

void test(const char* in, const char* expectedOut) {
	char* out = replaceSpaces(in);
	if (strcmp(out, expectedOut) == 0) {
		printf("PASS\n");
	} else {
		printf("FAIL: Got: %s; expected: %s\n", out, expectedOut);
	}
	free(out);
}

int main(int argc, char **argv) {
	test("", "");
	test("foobar", "foobar");
	test("abc def", "abc%20def");
	test("i like beer", "i%20like%20beer");
	return 0;
}