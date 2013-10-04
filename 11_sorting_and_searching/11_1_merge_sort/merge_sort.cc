#include <assert.h>
#include <iostream>
#include <vector>

const int MAX_NUM = 1000000;

static int numCompares = 0;

class MergeSort {
 public:
  static void sort(std::vector<int>& input);
 private:
  static void doSort(std::vector<int>& input, int first, int last);
};

void MergeSort::sort(std::vector<int>& input) {
  doSort(input, 0, input.size() - 1);
}

void MergeSort::doSort(std::vector<int>& input, int first, int last) {
  if (first == last) {
    return;
  }

  int partition = (first + last) / 2;
  doSort(input, first, partition);
  doSort(input, partition + 1, last);

  int firstPos = first, secondPos = partition + 1;
  std::vector<int> tmp;
  int remain = last - first + 1;
  while (remain-- > 0) {
    if ((firstPos <= partition) &&
        ((secondPos > last) || (input.at(firstPos) <= input.at(secondPos)))) {
      tmp.push_back(input.at(firstPos++));
    } else {
      tmp.push_back(input.at(secondPos++));
    }
    ++numCompares;
  }

  for (int i = 0; i < last - first + 1; ++i) {
    input[first + i] = tmp[i];
  }
}

void test(int size) {
  std::vector<int> v;
  int hash = 11;
  for (int i = 0; i < size; ++i) {
    hash = hash * 31 + i;
    if ((hash & 0x2) == 0x2) {
      v.insert(v.begin(), i);
    } else {
      v.push_back(i);
    }
  }
  
  MergeSort::sort(v);

  int prev = -1;
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    assert(*it > prev);
    prev = *it;
  }  

  std::cout << "For " << size << " elements, merge sorting required "
      << numCompares << " comparisons." << std::endl;
  numCompares = 0;
}

int main(int argc, char **argv) {
  for (int i = 1; i <= MAX_NUM; i *= 10) { test(i); }
  return 0;
}
