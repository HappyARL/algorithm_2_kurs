#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Stack {
 private:
  size_t top;
  std::vector<std::pair<int, int>> stack;
 public:
  Stack() {
    top = 0;
    stack.push_back(std::pair(0, 0));
  }
  ~Stack() {
    top = 0;
    stack.clear();
  }
  void Push(int val) {
    int new_min = stack[top].second < val ? stack[top].second : val;
    stack.push_back(std::pair(val, new_min));
    ++top;
  }

  void Pop() {
    stack.pop_back();
  }

  int Back() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      return main_arr[top];
    }
    return 0;
  }

  int StackSize() { return top; }

  int StackMin() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      return low_arr[top];
    }
    return 0;
  }

  void StackClear() {
    top = 0;
    std::cout << "ok" << std::endl;
  }
};





int main() {
  int test, elem;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "enqueue") {
      std::cin >> elem;
      Enqueue(elem);
    }
    if (cmd == "dequeue") {
      Dequeue();
    }
    if (cmd == "front") {
      Front();
    }
    if (cmd == "size") {
      Size();
    }
    if (cmd == "clear") {
      Clear();
    }
    if (cmd == "min") {
      Min();
    }
    test--;
  }
  return 0;
}
