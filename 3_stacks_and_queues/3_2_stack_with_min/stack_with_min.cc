#include <iostream>
#include <assert.h>

class MinStack {
 public:
  explicit MinStack(int capacity);
  ~MinStack();

  void push(int value);
  int pop();
  int size() const { return size_; }
  int head() const;
  int min() const;

 private:
  MinStack(const MinStack&);
  MinStack& operator=(const MinStack&);

  struct State {
    int value_;
    int min_;
  };

  friend std::ostream& operator<<(std::ostream&, const MinStack&);
  State* stack_;

  int size_;
  int capacity_;
};

std::ostream& operator<<(std::ostream& ostr, const MinStack& stack) {
  ostr << "Stack state:";
  ostr << "\n capacity: " << stack.capacity_;
  ostr << "\n     size: " << stack.size_;
  for (int i = 0; i < stack.size_; ++i) {
    ostr << "\n  lvl: " << i << " val: " << stack.stack_[i].value_;
    ostr << " min: " << stack.stack_[i].min_;
  }
  ostr << std::endl;
  return ostr;
}

class StackEmptyException {};
class StackFullException {};

MinStack::MinStack(int capacity)
    : stack_(NULL), size_(0), capacity_(capacity) {
  stack_ = new State[capacity];
}

MinStack::~MinStack() {
  delete [] stack_;
}

int MIN(int a, int b) {
  return a < b ? a : b;
}

void MinStack::push(int value) {
  if (size_ == capacity_) {
    throw new StackFullException;
  }
  stack_[size_].value_ = value;
  int min = value;
  if (size_ > 0) {
    min = MIN(value, stack_[size_ - 1].min_);
  }
  stack_[size_].min_ = min;
  ++size_;
}

int MinStack::pop() {
  if (size_ == 0) {
    throw new StackEmptyException;
  }
  --size_;
  return stack_[size_].value_;
}

int MinStack::head() const {
  if (size_ == 0) {
    throw new StackEmptyException;
  }
  return stack_[size_ - 1].value_; 
}

int MinStack::min() const {
  if (size_ == 0) {
    throw new StackEmptyException;
  }
  return stack_[size_ - 1].min_; 
}

int main(int argc, char **argv) {
  try {
    MinStack* ms = new MinStack(5);
    std::cout << *ms << std::endl;
    assert(ms->size() == 0);

    ms->push(3);
    std::cout << *ms << std::endl;
    assert(ms->size() == 1);
    assert(ms->head() == 3);
    assert(ms->min()  == 3);

    ms->push(1);
    std::cout << *ms << std::endl;
    assert(ms->size() == 2);
    assert(ms->head() == 1);
    assert(ms->min()  == 1);

    ms->push(2);
    std::cout << *ms << std::endl;
    assert(ms->size() == 3);
    assert(ms->head() == 2);
    assert(ms->min()  == 1);

    assert(ms->pop() == 2);
    std::cout << *ms << std::endl;
    assert(ms->size() == 2);
    assert(ms->head() == 1);
    assert(ms->min()  == 1);

    assert(ms->pop() == 1);
    std::cout << *ms << std::endl;
    assert(ms->size() == 1);
    assert(ms->head() == 3);
    assert(ms->min()  == 3);

    assert(ms->pop() == 3);
    std::cout << *ms << std::endl;
    assert(ms->size() == 0);
    delete ms;
  } catch (StackFullException* ex) {
    std::cerr << "stack full!" << std::endl;
  } catch (StackEmptyException* ex) {
    std::cerr << "stack empty!" << std::endl;
  }
  return 0;
}