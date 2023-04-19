#include <algorithm>
#include <iostream>
#include <string>

const int kLength = 2e5 + 5;

class Stack {
 private:
  int top_;
  int* main_arr_;
  int* min_arr_;

 public:
  Stack();
  ~Stack();
  void Push(int value);
  void Pop();
  void Back();
  void Size();
  void Min();
  void Clear();
};

Stack::Stack() {
  top_ = 0;
  main_arr_ = new int[kLength];
  min_arr_ = new int[kLength];
  min_arr_[0] = 1e9 + 9;
}

Stack::~Stack() {
  delete[] main_arr_;
  delete[] min_arr_;
}

void Stack::Push(int value) {
  top_++;
  main_arr_[top_] = value;
  min_arr_[top_] = std::min(min_arr_[top_ - 1], main_arr_[top_]);
  std::cout << "ok" << std::endl;
}

void Stack::Pop() {
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    int pop_value = main_arr_[top_];
    top_--;
    std::cout << pop_value << std::endl;
  }
}

void Stack::Back() {
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << main_arr_[top_] << std::endl;
  }
}

void Stack::Size() { std::cout << top_ << std::endl; }

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

int main() {
  int test, num;
  std::cin >> test;
  Stack stack;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "push") {
      std::cin >> num;
      stack.Push(num);
    }
    if (cmd == "pop") {
      stack.Pop();
    }
    if (cmd == "back") {
      stack.Back();
    }
    if (cmd == "min") {
      stack.Min();
    }
    if (cmd == "size") {
      stack.Size();
    }
    if (cmd == "clear") {
      stack.Clear();
    }
    test--;
  }
  return 0;
}
