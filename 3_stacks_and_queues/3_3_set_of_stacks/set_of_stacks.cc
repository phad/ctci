#include <assert.h>
#include <iostream>
#include <vector>

#include "../stack.h"

class SetStacks {
 public:
  SetStacks(int capacity = 10);

  bool isEmpty() const;
  int size() const;
  void push(int value);
  int pop();
  int head() const;
  int peek(int pos) const;

  void output() const;

 private:
  SetStacks(const SetStacks&);
  SetStacks& operator=(const SetStacks&);

  Stack* currentStack() const;
  Stack* currentMaybeNewStack();

  std::vector<Stack*> stacks_;
  int capacity_;
};

SetStacks::SetStacks(int capacity)
    : capacity_(capacity) {
}

bool SetStacks::isEmpty() const {
  return stacks_.empty()
      || stacks_.back()->size() == 0;
}

int SetStacks::size() const {
  if (stacks_.empty()) {
    return 0;
  }
  return capacity_ * (stacks_.size() - 1)
      + stacks_.back()->size();
}

void SetStacks::push(int value) {
  Stack* current = currentMaybeNewStack();
  current->push(value);
}

int SetStacks::pop() {
  Stack* current = currentStack();
  int result = current->pop();
  if (current->size() == 0) {
    stacks_.pop_back();
    delete current;
  }
  return result;
}

int SetStacks::head() const {
  Stack* current = currentStack();
  return current->head();
}

int SetStacks::peek(int pos) const {
  int sz = size();
  if (pos > sz) {
    throw new StackAccessException;
  }
  int stackIndex = pos / capacity_;
  return stacks_[stackIndex]->peek(pos % capacity_);
}

void SetStacks::output() const {
  std::cout << "SetStacks:" << std::endl;
  for (std::vector<Stack*>::const_iterator it = stacks_.begin();
      it != stacks_.end();
      ++it) {
    std::cout << "  " << **it;
  }
}

Stack* SetStacks::currentStack() const {
  if (stacks_.empty()) {
    return NULL;
  } else {
    return stacks_.back();
  }
}

Stack* SetStacks::currentMaybeNewStack() {
  Stack* current = currentStack();
  if (!current || current->size() == capacity_) {
    current = new Stack(capacity_);
    stacks_.push_back(current);
  }
  return current;
}

int main(int argc, char **argv) {
  try {
    SetStacks ss(5);

    for (int i = 0; i < 50; ++i) {
      ss.push(i);
    }

    for (int i = 0; i < 50; ++i) {
      assert(ss.peek(i) == i);
    }

    for (int i = 49; i >= 0; --i) {
      assert(ss.pop() == i);
    }

  } catch (StackFullException* ex) {
    std::cerr << "stack full!" << std::endl;
  } catch (StackEmptyException* ex) {
    std::cerr << "stack empty!" << std::endl;
  }
  return 0;
}
