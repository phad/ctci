#include <stdlib.h>
#include <stdio.h>

typedef unsigned short uint8;

const uint8 REPEAT_START  = 0x80;

typedef enum {
	EInLiteral = 0,
	EInRepeat = 1
} State;

char emit(char ch) {
	/* printf("Emit: %c (%d)\n", ch, (uint8)ch); */
	return ch;
}

void emitModify(char ch) {
	/* printf("Updated: %c (%d)\n", ch, (uint8)ch); */
}

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
		/* printf("In: %c Previous: %c State: %s RptCnt: %d LastTagIdx: %d\n",
			*iptr, previous, (state == EInLiteral ? "inlit" : "inrpt"),
			repeatCount, lastTagIndex);  
		*/
		if (*iptr == previous) {
			switch(state) {
				case EInLiteral:
					state = EInRepeat;
					lastTagIndex = optr - out;
					*optr++ = emit(REPEAT_START);
					*optr++ = emit(*iptr);
					repeatCount = 1;
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
					emitModify(*(out + lastTagIndex));
					state = EInLiteral;
					repeatCount = 0;
					break;
			}
			*optr++ = emit(*iptr);
		}
		previous = *iptr++;
	}
	// Finally update last tag if in repeat
	if (state == EInRepeat) {
		*(out + lastTagIndex) +=  repeatCount;
		emitModify(*(out + lastTagIndex));
	}

	return out;
}

void test(const char* input, const char* expectedCompressed) {
	char* compressed = compressString(input);
	if (strcmp(compressed, expectedCompressed) == 0) {
		printf("PASS: orig len %d; compressed len %d\n", strlen(input), strlen(compressed));
	} else {
		printf("FAIL: got %s; expected %s\n", compressed, expectedCompressed);
	}
	free(compressed);
}

int main(int argc, char **argv) {
	test("paul", "paul");
	test("hello", "hel\x81lo");
	test("aaaa", "a\x83""a");
	test("bbbbbbbb", "b\x87""b");
	test("oppqqqrrrrssssstuuuuvvvww",
		 "op\x81pq\x82qr\x83rs\x84stu\x83uv\x82vw\x81w");
	return 0;
}