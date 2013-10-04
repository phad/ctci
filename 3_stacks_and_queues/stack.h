#ifndef STACK_H
#define STACK_H

#include <iostream>

class Stack {
 public:
  explicit Stack(int capacity = 10);
  ~Stack();

  void push(int value);
  int pop();
  int size() const { return size_; }
  int head() const;
  int peek(int pos) const;

 private:
  Stack(const Stack&);
  Stack& operator=(const Stack&);

  friend std::ostream& operator<<(std::ostream&, const Stack&);
  int* stack_;

  int size_;
  int capacity_;
};

class StackEmptyException {};
class StackFullException {};
class StackAccessException {};

#endif
