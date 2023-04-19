#include <algorithm>
#include <iostream>
#include <string>

const int kLength = 2e5 + 1;

class Stack {
 private:
  int top_;
  int* main_arr_;
  int* min_arr_;

 public:
  Stack();
  ~Stack();
  void Push(int value);
  int Pop();
  void Back();
  int Size();
  void Min();
  void Clear();
};

Stack::Stack() {
  top_ = 0;
  main_arr_ = new int[kLength];
  min_arr_ = new int[kLength];
  min_arr_[0] = 1e9 + 1;
}

Stack::~Stack() {
  delete[] main_arr_;
  delete[] min_arr_;
}

void Stack::Push(int value) {
  top_++;
  main_arr_[top_] = value;
  min_arr_[top_] = std::min(min_arr_[top_ - 1], main_arr_[top_]);
}

int Stack::Pop() {
  int pop_value = main_arr_[top_];
  top_--;
  return pop_value;
}

void Stack::Back() {
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << main_arr_[top_] << std::endl;
  }
}

int Stack::Size() { return top_; }

void Stack::Min() {
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << min_arr_[top_] << std::endl;
  }
}

void Stack::Clear() {
  top_ = 0;
  std::cout << "ok" << std::endl;
}

class Queue {
 private:
  Stack stack_left_;
  Stack stack_right_;

 public:
  Queue();
  ~Queue();
  void Enqueue(int value);
  void Dequeue();
  void Front();
  void Size();
  void Clear();
  void Min();
};

Queue::Queue() {}

Queue::~Queue() {}

void Queue::Enqueue(int value) {
  stack_left_.Push(value);
  std::cout << "ok" << std::endl;
}

void Queue::Dequeue() {
  while (stack_left_.Size() != 0) {
    int num = stack_left_.Pop();
    stack_right_.Push(num);
  }
  if (stack_right_.Size() == 0) { 
    std::cout << "error" << std::endl;
  } else {
    std::cout << stack_right_.Pop() << std::endl;
  }
  while (stack_right_.Size() != 0) {
    int num = stack_right_.Pop();
    stack_left_.Push(num);
  }
}

void Queue::Front() { stack_left_.Back(); }

void Queue::Size() { std::cout << stack_left_.Size() << std::endl; }

void Queue::Clear() { stack_left_.Clear(); }

void Queue::Min() { stack_left_.Min(); }

int main() {
  int test, num;
  std::cin >> test;
  Queue queue;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "enqueue") {
      std::cin >> num;
      queue.Enqueue(num);
    }
    if (cmd == "dequeue") {
      queue.Dequeue();
    }
    if (cmd == "front") {
      queue.Front();
    }
    if (cmd == "min") {
      queue.Min();
    }
    if (cmd == "size") {
      queue.Size();
    }
    if (cmd == "clear") {
      queue.Clear();
    }
    test--;
  }
  return 0;
}
