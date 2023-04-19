#include <iostream>

const int kLength = 1e5 + 1;

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
  int Back();
  int Size();
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
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  }
  int pop_value = main_arr_[top_];
  top_--;
  return pop_value;
}

int Stack::Back() { return main_arr_[top_]; }

int Stack::Size() { return top_; }

int main() {
  Stack stack;
  std::string brackets;
  std::cin >> brackets;
  for (int i = 0; i < (int)brackets.length(); ++i) {
    if (brackets[i] == '[' || brackets[i] == '(' || brackets[i] == '{') {
      stack.Push(brackets[i]);
    } else {
      bool pair = false;
      switch (brackets[i]) {
        case ']':
          pair = (stack.Back() == '[');
          break;
        case '}':
          pair = (stack.Back() == '{');
          break;
        case ')':
          pair = (stack.Back() == '(');
          break;
      }
      if (pair) {
        stack.Pop();
      } else {
        std::cout << "NO" << std::endl;
        return 0;
      }
    }
  }
  std::cout << ((stack.Size() == 0) ? "YES" : "NO") << std::endl;
  return 0;
}
