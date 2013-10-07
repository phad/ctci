#include <assert.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

// Uncomment to see the partitioning of the int vector
//#define DEBUG

using namespace std;

const int MAX_NUM = 1000000;
static int numCompares = 0;

class QuickSort {
 public:
  static void sort(vector<int>& input);
 private:
  static int partition(vector<int>& input, int lo, int hi);
  static void doSort(vector<int>& input, int first, int last);
};

void out(vector<int>& v) {
  cout << "Vec: ";
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void out(vector<int>& v, int lo, int j, int hi) {
  cout << "Vec: ";
  int k = 0;
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    if (k == lo)
      cout << '[';
    if (k == j)
      cout << '(';
    cout << *it;
    if (k == j)
      cout << ')';
    if (k == hi)
      cout << ']';
    cout << " ";
    ++k;
  }
  cout << endl;
}

void QuickSort::sort(vector<int>& input) {
  // Shuffle to produce more deterministic behaviour. Without
  // shuffling the pathological case of an input in descending order
  // performs almost an order worse than in the shuffled case.  The
  // saving is well worth the cost of the shuffle.
  random_shuffle(input.begin(), input.end());
#ifdef DEBUG
  out(input);
#endif
  doSort(input, 0, input.size() - 1);
}

void swap(vector<int>& input, int a, int b) {
  int tmp = input[a];
  input[a] = input[b];
  input[b] = tmp;
}

int QuickSort::partition(vector<int>& input, int lo, int hi) {
  int partnIdx = lo;
  int scanLtIdx = lo, scanGtIdx = hi + 1;
  while (true) {
    while (input[++scanLtIdx] < input[partnIdx]) {
      ++numCompares;
      if (scanLtIdx == hi) break;
    }
    while (input[--scanGtIdx] > input[partnIdx]) {
      ++numCompares;
      if (scanGtIdx == lo) break;
    }
    if (scanLtIdx >= scanGtIdx) break;
    swap(input, scanLtIdx, scanGtIdx);
  }
  swap(input, partnIdx, scanGtIdx);
  // Now, every element < scanGtIdx is less than the partition element,
  // and every element > scanGtIdx is greater than the partition element.
  return scanGtIdx;
}

void QuickSort::doSort(vector<int>& input, int lo, int hi) {
  if (hi <= lo) {
    return;
  }
  int j = partition(input, lo, hi);
  // The element at index j is correctly positioned so we now recurse
  // to sort the range below j and the range above j.
#ifdef DEBUG
  out(input, lo, j, hi);
#endif
  doSort(input, lo, j - 1);
  doSort(input, j + 1, hi);
}

void test(int size) {
  vector<int> v;
  for (int i = size - 1; i >= 0; --i) {
    v.push_back(i);
  }
  
  QuickSort::sort(v);

  int prev = -1;
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    assert(*it > prev);
    prev = *it;
  }  

  cout << "For " << size << " elements, Quick sorting required "
      << numCompares << " comparisons." << endl;
  numCompares = 0;
}

int main(int argc, char **argv) {
  std::srand ( unsigned ( std::time(0) ) );
  for (int i = 1; i <= MAX_NUM; i *= 10) { test(i); }
  return 0;
}
