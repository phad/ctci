#include <iostream>
#include <map>
#include <string>

using namespace std;

string find_unique_chars(const string& in) {
  map<wchar_t, bool> seen;
  string out;
  for (string::const_iterator it = in.begin(); it != in.end(); ++it) {
    if (seen[*it])
      continue;
    out += *it;
    seen[*it] = true;
  }
  return out;
}

int main(int argc, char **argv) {
  cout << find_unique_chars("Hello world!") << endl;
  return 0;
}

