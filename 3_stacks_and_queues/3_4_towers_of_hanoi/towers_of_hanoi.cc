#include <iostream>
#include <assert.h>

class Stack {
 public:
  explicit Stack(int capacity = 10);
  ~Stack();

  void push(int value);
  int pop();
  int size() const { return size_; }
  int head() const;

 private:
  Stack(const Stack&);
  Stack& operator=(const Stack&);

  friend std::ostream& operator<<(std::ostream&, const Stack&);
  int* stack_;

  int size_;
  int capacity_;
};

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

class StackEmptyException {};
class StackFullException {};

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

void output(Stack* pins) {
  for (int p = 0; p < 3; ++p) {
    std::cout << "Pin: " << p << " " << pins[p];
  }
  std::cout << std::endl;
}

int kOther[3][3] = { {-1, 2, 1}, {2, -1, 0}, {1, 0, -1} };

void move_n_disks(int n, Stack* pins, int from, int to, int& iter) {
  // move n−1 discs from A to B. This leaves disc n alone on peg A
  assert(from != to);
  int n_1_to = kOther[from][to];
  if (n > 1) {
    move_n_disks(n - 1, pins, from, n_1_to, iter);
  }

  // move disc n from A to C
  std::cout << "State at iteration: " << iter << std::endl;
  std::cout << "Moving from pin " << from << " to pin " << to << std::endl;
  pins[to].push(pins[from].pop());
  ++iter;
  output(pins);

  // move n−1 discs from B to C so they sit on disc n
  if (n > 1) {
    move_n_disks(n - 1, pins, n_1_to, to, iter);
  }
}

int main(int argc, char **argv) {
  try {
    Stack pins[3];
    pins[0].push(5);
    pins[0].push(4);
    pins[0].push(3);
    pins[0].push(2);
    pins[0].push(1);
    output(pins);
    int iter = 0;
    move_n_disks(5, pins, 0, 2, iter);
  } catch (StackFullException* ex) {
    std::cerr << "stack full!" << std::endl;
  } catch (StackEmptyException* ex) {
    std::cerr << "stack empty!" << std::endl;
  }
  return 0;
}
