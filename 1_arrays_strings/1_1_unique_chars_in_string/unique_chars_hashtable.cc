#include <iostream>
#include <string>

#include "../hash_table.h"

using namespace std;

string find_unique_chars(const string& in) {
  HashTable<bool> seen(256);
  string out;
  for (string::const_iterator it = in.begin(); it != in.end(); ++it) {
    string k;
    k += *it;
    if (seen.has_key(k))
      continue;
    out += k;
    seen.put(k, true);
  }
  return out;
}

int main(int argc, char **argv) {
  cout << find_unique_chars("Hello world!") << endl;
  return 0;
}

