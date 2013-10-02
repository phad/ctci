#include <stdlib.h>
#include <stdio.h>

typedef unsigned short uint8;

const uint8 LITERAL_START = 0x80;
const uint8 REPEAT_START  = 0x40;

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
    int literalCount = 0;
	const char* iptr = in;
	char previous = '\0';

	char* optr = out;
    int lastTagIndex = 0;
    *optr++ = emit(LITERAL_START); 

	while (*iptr) {
		/* printf("In: %c Previous: %c State: %s LitCnt: %d RptCnt: %d LastTagIdx: %d\n",
			*iptr, previous, (state == EInLiteral ? "inlit" : "inrpt"),
			literalCount, repeatCount, lastTagIndex);  
		*/
		if (*iptr == previous) {
			switch(state) {
				case EInLiteral:
					*(out + lastTagIndex) += literalCount;
					emitModify(*(out + lastTagIndex));
					state = EInRepeat;
					lastTagIndex = optr - out;
					*optr++ = emit(REPEAT_START);
					*optr++ = emit(*iptr);
					repeatCount = 1;
					literalCount = 0;
					break;
				case EInRepeat:
					++repeatCount;
					break;
			}
		} else {
			switch(state) {
				case EInLiteral:
					++literalCount;
					break;
				case EInRepeat:
					*(out + lastTagIndex) += repeatCount;
					emitModify(*(out + lastTagIndex));
					state = EInLiteral;
					lastTagIndex = optr - out;
					*optr++ = emit(LITERAL_START);
					repeatCount = 0;
					literalCount = 1;
					break;
			}
			*optr++ = emit(*iptr);
		}
		previous = *iptr++;
	}
	// Finally update last tag
	*(out + lastTagIndex) += (state == EInLiteral ? literalCount : repeatCount);
	emitModify(*(out + lastTagIndex));

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
	test("paul", "\x84paul");
	test("hello", "\x83hel\x41l\x81o");
	test("aaaa", "\x81""a\x43""a");
	test("bbbbbbbb", "\x81""b\x47""b");
	test("oppqqqrrrrssssstuuuuvvvww",
		 "\x82op\x41p\x81q\x42q\x81r\x43r\x81s\x44s\x82tu\x43u\x81v\x42v\x81w\x41w");
	return 0;
}