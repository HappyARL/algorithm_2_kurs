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
    low_arr[0] = 0;
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

  int Stack_Size() {
    return top;
  }

  int Stack_Min() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      return low_arr[top];
    }
    return 0;
  }

  void Stack_Clear() {
    top = 0;
    std::cout << "ok" << std::endl;
  }
};

class Queue {
 private:
  Stack l;
  Stack r; 
 public:
  void shift(Stack l, Stack r) {
    while(l.Stack_Size() > 0) {
      r.Push(l.Pop());
      l.Pop();
    }
  }
  void enqueue(int num) {
    l.Push(num);
    std::cout << "ok" << std::endl;
  }
  int dequeue() {
    if(l.top == 0) {
      std::cout << "error" << std::endl;    
    }
    if(r.Stack_Size() == 0) {
      shift(l, r);
    }
    std::cout << r.Pop() << std::endl;
    return 0;
  }
  void front() {
    if(l.top == 0) {
      std::cout << "error" << std::endl;    
    }
    std::cout << l.Back() << std::endl;
  }
  int size() {
    std::cout << l.Stack_Size() + r.Stack_Size() << std::endl;
    return 0;
  }
  void clear() {
    l.Stack_Clear();
  }
  int min() {
    if(l.top == 0) {
      std::cout << "error" << std::endl;    
    }
    std::cout << l.Stack_Min() << std::endl;
    return 0;
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
      q.enqueue(num);
    }
    if (cmd == "dequeue") {
      q.dequeue();
    }
    if (cmd == "front") {
      q.front();
    }
    if (cmd == "size") {
      q.size();
    }
    if (cmd == "clear") {
      q.clear();
    }
    if (cmd == "min") {
      q.min();
    }
    test--;
  }
  return 0;
}
