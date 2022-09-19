#include <algorithm>
#include <iostream>
#include <string>

const int kLength = 2e5 + 5;
class Stack {
 public:
  int top;
  int main_arr[kLength];
  int low_arr[kLength];
  Stack() {
    top = 0;
    low_arr[0] = 1e9 + 9;
  }
  void Push(int val) {
    top++;
    main_arr[top] = val;
    low_arr[top] = std::min(low_arr[top - 1], main_arr[top]);
  }

  int Pop() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      int pop_value = main_arr[top];
      top--;
      return pop_value;
    }
    return 0;
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

class Queue {
 private:
  Stack l_;
  Stack r_;

 public:
  void Enqueue(int num) {
    l_.Push(num);
    std::cout << "ok" << std::endl;
  }
  void Dequeue() {
    if (l_.top == 0) {
      std::cout << "error" << std::endl;
    } else {
      if (r_.top == 0) {
        while (r_.StackSize() == 0) {
          while (l_.StackSize() != 0) {
            int num = l_.Pop();
            r_.Push(num);
          }
        }
      }
      std::cout << r_.Pop() << std::endl;
    }
  }
  void Front() {
    if (r_.StackSize() != 0) {
      while (l_.StackSize() == 0) {
        while (r_.StackSize() != 0) {
          int num = r_.Pop();
          l_.Push(num);
        }
      }
    }
    if (l_.top == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << l_.Back() << std::endl;
    }
  }
  int Size() {
    std::cout << l_.StackSize() + r_.StackSize() << std::endl;
    return 0;
  }
  void Clear() {
    if (r_.StackSize() != 0) {
      while (l_.StackSize() == 0) {
        while (r_.StackSize() != 0) {
          int num = r_.Pop();
          l_.Push(num);
        }
      }
    }
    l_.StackClear();
  }
  void Min() {
    if (r_.StackSize() != 0) {
      while (l_.StackSize() == 0) {
        while (r_.StackSize() != 0) {
          int num = r_.Pop();
          l_.Push(num);
        }
      }
    }
    if (l_.top == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << l_.StackMin() << std::endl;
    }
  }
};
int main() {
  Queue q;
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "enqueue") {
      std::cin >> num;
      q.Enqueue(num);
    }
    if (cmd == "dequeue") {
      q.Dequeue();
    }
    if (cmd == "front") {
      q.Front();
    }
    if (cmd == "size") {
      q.Size();
    }
    if (cmd == "clear") {
      q.Clear();
    }
    if (cmd == "min") {
      q.Min();
    }
    test--;
  }
  return 0;
}
