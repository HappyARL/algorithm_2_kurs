#include <iostream>
#include <string>

class Stack {
 public:
  int top;
  int low;
  int length;
  int* main_arr;
  int* low_arr;

  Stack() {
    top = -1;
    low = 1;
    length = 1;
    main_arr = new int[length];
    low_arr = new int[length];
    for (int i = 0; i < length; i++) {
      main_arr[i] = 0;
      low_arr[i] = 0;
    }
  }

  void Push(int val) {
    if (top == length) {
      std::cout << "error" << std::endl;
    } else {
      length++;
      top++;
      main_arr[top] = val;
      if (val <= low) {
        low = val;
        low_arr[top] = low;
      } else {
        low_arr[top] = low;
      }
      std::cout << "ok" << std::endl;
    }
  }

  void Pop() {
    if (top == -1) {
      std::cout << "error" << std::endl;
    } else {
      int pop_value = main_arr[top];
      main_arr[top] = 0;
      low_arr[top] = 0;
      top--;
      length--;
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
    for (int i = 0; i < length; i++) {
      main_arr[i] = 0;
      low_arr[i] = 0;
    }
    std::cout << "ok" << std::endl;
  }
};

int main() {
  Stack s1;
  int test;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "push") {
      int num;
      std::cin >> num;
      s1.Push(num);
    }
    if (cmd == "pop") {
      s1.Pop();
    }
    if (cmd == "back") {
      s1.Back();
    }
    if (cmd == "min") {
      s1.Min();
    }
    if (cmd == "size") {
      s1.Size();
    }
    if (cmd == "clear") {
      s1.Clear();
    }
  }
  delete[] s1.main_arr;
  delete[] s1.low_arr;
}
