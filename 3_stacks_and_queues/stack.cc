#include "stack.h"

std::ostream& operator<<(std::ostream& ostr, const Stack& stack) {
  ostr << "Stack state:";
  ostr << " capacity: " << stack.capacity_;
  ostr << " size: " << stack.size_;
  ostr << " values: ";
  for (int i = 0; i < stack.size_; ++i) {
    ostr << stack.stack_[i] << " ";
  }
  ostr << std::endl;
  return ostr;
}

Stack::Stack(int capacity)
    : stack_(NULL), size_(0), capacity_(capacity) {
  stack_ = new int[capacity];
}

Stack::~Stack() {
  delete [] stack_;
}

void Stack::push(int value) {
  if (size_ == capacity_) {
    throw new StackFullException;
  }
  stack_[size_] = value;
  ++size_;
}

int Stack::pop() {
  if (size_ == 0) {
    throw new StackEmptyException;
  }
  --size_;
  return stack_[size_];
}

int Stack::head() const {
  if (size_ == 0) {
    throw new StackEmptyException;
  }
  return stack_[size_ - 1]; 
}

int Stack::peek(int pos) const {
  if (pos >= size_) {
    throw new StackAccessException;
  }
  return stack_[pos];
}
