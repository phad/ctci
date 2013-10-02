#include <iostream>
#include <string>

using namespace std;

string replaceSpaces(const string& in) {
	string out;
	for(string::const_iterator it = in.begin(); it != in.end(); ++it) {
		if (*it == ' ') {
			out += "%20";
		} else {
			out += *it;
		}
	}
	return out;
}

void test(const string& in, const string& expectedOut) {
	string out = replaceSpaces(in);
	if (out == expectedOut) {
		cout << "PASS" << endl;
	} else {
		cerr << "FAIL: Got: " << out << "; expected: " << expectedOut << endl;
	}
}

int main(int argc, char **argv) {
	test("abc def", "abc%20def");
	test("i like beer", "i%20like%20beer");
	return 0;
}