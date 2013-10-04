#include <iostream>
#include <assert.h>

class TripleStack {
 public:
  explicit TripleStack(int capacity);
  ~TripleStack();

  void push(int stackIdx, int value);
  int pop(int stackIdx);
  int size(int stackIdx);
  int head(int stackIdx) const;

 private:
  TripleStack(const TripleStack&);
  TripleStack& operator=(const TripleStack&);

  int headIndex(int stackIdx) const;
  void assertStackIdx(int stackIdx) const;

  friend std::ostream& operator<<(std::ostream&, const TripleStack&);
  int* stack_;

  int sizes_[3];
  int capacity_;
};

class StackEmptyException {
 public:
  StackEmptyException(int stackIdx) : idx_(stackIdx) {}
  int idx_;  
};

class StackFullException {
 public:
  StackFullException(int stackIdx) : idx_(stackIdx) {}
  int idx_;  
};

TripleStack::TripleStack(int capacity)
    : stack_(NULL), capacity_(capacity) {
  for (int i = 0; i < 3; ++i) {
    sizes_[i] = 0;
  }
  stack_ = new int[3 * capacity];
}

TripleStack::~TripleStack() {
  delete [] stack_;
}

void TripleStack::push(int stackIdx, int value) {
  assertStackIdx(stackIdx);
  if (sizes_[stackIdx] == capacity_) {
    throw new StackFullException(stackIdx);
  }
  stack_[headIndex(stackIdx)] = value;
  ++sizes_[stackIdx];
}

int TripleStack::pop(int stackIdx) {
  assertStackIdx(stackIdx);
  if (sizes_[stackIdx] == 0) {
    throw new StackEmptyException(stackIdx);
  }
  --sizes_[stackIdx];
  return stack_[headIndex(stackIdx)];
}

int TripleStack::size(int stackIdx) {
  assertStackIdx(stackIdx);
  return sizes_[stackIdx];
}

int TripleStack::head(int stackIdx) const {
  assertStackIdx(stackIdx);
  if (sizes_[stackIdx] == 0) {
    throw new StackEmptyException(stackIdx);
  }
  return stack_[headIndex(stackIdx)];
}

int TripleStack::headIndex(int stackIdx) const {
  assertStackIdx(stackIdx);
  return stackIdx * capacity_ + sizes_[stackIdx];
}

void TripleStack::assertStackIdx(int stackIdx) const {
  assert(stackIdx >= 0 && stackIdx < 3);
}

std::ostream& operator<<(std::ostream& ostr, const TripleStack& ts) {
  for (int idx = 0; idx < 3; ++idx) {
    ostr << "Stack #" << idx << " size: " << ts.sizes_[idx] << std::endl;
    ostr << "  values: ";
    for (int elem = 0; elem < ts.sizes_[idx]; ++elem) {
      ostr << ts.stack_[idx * ts.capacity_ + elem] << " ";
    }
    ostr << std::endl;
  }
  return ostr;
}

int main(int argc, char **argv) {
  TripleStack ts(10);
  std::cout << ts << std::endl;
  for (int i = 0; i < 3; ++i) { assert(ts.size(i) == 0); }

  ts.push(0, 1);
  ts.push(2, 1);
  ts.push(0, 2);
  ts.push(0, 3);
  ts.push(1, 1);
  ts.push(1, 2);
  ts.push(2, 2);
  ts.push(1, 3);
  ts.push(1, 4);
  std::cout << ts << std::endl;

  assert(ts.pop(1) == 4);
  assert(ts.pop(1) == 3);
  assert(ts.pop(2) == 2);
  assert(ts.pop(2) == 1);
  assert(ts.pop(0) == 3);
  assert(ts.pop(1) == 2);
  assert(ts.pop(0) == 2);
  assert(ts.pop(0) == 1);
  assert(ts.pop(1) == 1);

  std::cout << ts << std::endl;
  for (int i = 0; i < 3; ++i) { assert(ts.size(i) == 0); }

  try {
    ts.pop(2);
  } catch (StackEmptyException* ex) {
    std::cerr << "Stack " << ex->idx_ << " empty!" << std::endl; 
  }
  return 0;
}
