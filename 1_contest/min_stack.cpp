#include <algorithm>
#include <iostream>
#include <string>

const int kLength = 2e5 + 5;
int top = 0;
int main_arr[kLength];
int low_arr[kLength];

void Push(int val) {
  top++;
  main_arr[top] = val;
  low_arr[top] = std::min(low_arr[top - 1], main_arr[top]);
  std::cout << "ok" << std::endl;
}

void Pop() {
  if (top == 0) {
    std::cout << "error" << std::endl;
  } else {
    int pop_value = main_arr[top];
    top--;
    std::cout << pop_value << std::endl;
  }
}

int Back() {
  if (top == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << main_arr[top] << std::endl;
  }
  return 0;
}

int Size() {
  std::cout << top << std::endl;
  return 0;
}

int Min() {
  if (top == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << low_arr[top] << std::endl;
  }
  return 0;
}

void Clear() {
  top = 0;
  std::cout << "ok" << std::endl;
}

int main() {
  int test, num;
  std::cin >> test;
  low_arr[0] = 1e9 + 9;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "push") {
      std::cin >> num;
      Push(num);
    }
    if (cmd == "pop") {
      Pop();
    }
    if (cmd == "back") {
      Back();
    }
    if (cmd == "min") {
      Min();
    }
    if (cmd == "size") {
      Size();
    }
    if (cmd == "clear") {
      Clear();
    }
    test--;
  }
  return 0;
}