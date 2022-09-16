#include <iostream>

const int kLength = 2e5 + 5;
int top = -1;
int low = 1e9;
int main_arr[kLength];
int low_arr[kLength];

void Push(int val) {
  main_arr[++top] = val;
  if (val <= low) {
    low = val;
    low_arr[top] = low;
  } else {
    low_arr[top] = low;
  }
  std::cout << "ok" << std::endl;
}

void Pop() {
  if (top == -1) {
    std::cout << "error" << std::endl;
  } else {
    int pop_value = main_arr[top];
    top--;
    std::cout << pop_value << std::endl;
  }
}

int Back() {
  if (top == -1) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << main_arr[top] << std::endl;
  }
  return 0;
}

int Size() {
  std::cout << top + 1 << std::endl;
  return 0;
}

int Min() {
  if (top == -1) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << low_arr[top] << std::endl;
  }
  return 0;
}

void Clear() {
  for (int i = 0; i < top; i++) {
    main_arr[i] = 0;
    low_arr[i] = 0;
  }
  top = -1;
  low = 1;
  std::cout << "ok" << std::endl;
}

int main() {
  int test, num;
  std::cin >> test;
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