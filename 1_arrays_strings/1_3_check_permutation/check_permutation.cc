#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool arePermuted(const string& left, const string& right) {
	string leftSorted = left;
	sort(leftSorted.begin(), leftSorted.end());

	string rightSorted = right;
	sort(rightSorted.begin(), rightSorted.end());

	return leftSorted == rightSorted;
}

void test(const string& left, const string& right) {
	cout << left << ", " << right << ": " << arePermuted(left, right) << endl;
}

int main(int argc, char **argv) {
	test("the eyes", "they see");
	test("i like you", "you like me");
	return 0;
}