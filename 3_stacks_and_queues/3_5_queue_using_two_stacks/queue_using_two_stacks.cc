#include <iostream>
#include <assert.h>

#include "../stack.h"

class Queue {
 public:
  Queue(int capacity = 10);

  bool isEmpty() const;
  int size() const;
  void pushBack(int value);
  int popFront();

  void output() const;

 private:
  Queue(const Queue&);
  Queue& operator=(const Queue&);

  void drain();

  Stack in_;
  Stack out_;
  int capacity_;
};

Queue::Queue(int capacity)
    : in_(capacity), out_(capacity), capacity_(capacity) {
}

bool Queue::isEmpty() const {
  return size() == 0;
}

int Queue::size() const {
  return in_.size() + out_.size();
}

void Queue::pushBack(int value) {
  in_.push(value);
}

int Queue::popFront() {
  drain();
  return out_.pop();
}

void Queue::output() const {
  std::cout << "Queue:";
  for (int i = in_.size(); i > 0; i--) {
    std::cout << " " << in_.peek(i - 1);
  }
  std::cout << " ][";
  for (int o = 0; o < out_.size(); o++) {
    std::cout << " " << out_.peek(o);
  }
  std::cout << std::endl;
}

void Queue::drain() {
  if (out_.size() == 0) {
    while (in_.size() > 0) {
      out_.push(in_.pop());
    }
  }
}

int main(int argc, char **argv) {
  try {
    Queue q(5);
    q.output();

    for (int i = 1; i <= 5; ++i) {
      q.pushBack(i);
      assert(q.size() == i);
      q.output();
    }

    for (int i = 1; i <= 5; ++i) {
      assert(q.popFront() == i);
      q.pushBack(i + 5);
      assert(q.size() == 5);
      q.output();
    }

    for (int i = 1; i <= 5; ++i) {
      assert(q.popFront() == i + 5);
      assert(q.size() == 5 - i);
      q.output();
    }

  } catch (StackFullException* ex) {
    std::cerr << "stack full!" << std::endl;
  } catch (StackEmptyException* ex) {
    std::cerr << "stack empty!" << std::endl;
  }
  return 0;
}
