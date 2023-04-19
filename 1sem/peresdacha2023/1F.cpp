#include <iostream>

const int kLength = 2e5 + 5;

class Stack {
 private:
  int top_;
  int* main_arr_;

 public:
  Stack();
  ~Stack();
  void Push(int value);
  int Pop();
  void Size();
  int Answer();
};

Stack::Stack() {
  top_ = 0;
  main_arr_ = new int[kLength];
}

Stack::~Stack() {
  delete[] main_arr_;
}

void Stack::Push(int value) {
  top_++;
  main_arr_[top_] = value;
}

int Stack::Pop() {
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    int pop_value = main_arr_[top_];
    top_--;
    return pop_value;
  }
  return 0;
}

int Stack::Answer() {
  return main_arr_[top_];
}

int main() {
  Stack stack;
  int* arr = new int[10];
  for (int i = 0; i < 10; ++i) {
    
  }
  std::cout << stack.Answer() << std::endl;
  return 0;
}
