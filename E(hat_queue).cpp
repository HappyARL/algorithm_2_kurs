#include <iostream>
#include <cmath>

const int kkLength = 10;

class Stack {
 public:
  int top = -1;
  int low = 1;
  int main_arr[kkLength / 2];
  int low_arr[kkLength /  2];
  Stack() {
    top = -1;
  }

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

  int Pop() {
    if (top == -1) {
      std::cout << "error" << std::endl;
    } else {
      int pop_value = main_arr[top];
      top--;
      return pop_value;
    }
    return 0;
  }

  int Back() {
    if (top == -1) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << main_arr[top] << std::endl;
    }
    return 0;
  }

  int stack_size() {
    return top + 1;
  }

  int stack_min() {
    if (top == -1) {
      std::cout << "error" << std::endl;
    } else {
      return low_arr[top];
    }
    return 0;
  }

  void stack_clear() {
    for (int i = 0; i < top; i++) {
      main_arr[i] = 0;
      low_arr[i] = 0;
    }
    top = -1;
    low = 1;
    std::cout << "ok" << std::endl;
  }
}st;

void shift(Stack l, Stack r) {
  while(l.stack_size() > 0) {
    r.Push(l.Pop());
    l.Pop();
  }
}
void enqueue(Stack l, Stack r, int val) {
  l.Push(val);
}
void dequeue(Stack l, Stack r) {
  if(l.top == -1) {
    std::cout << "error" << std::endl;
  }
  if(r.stack_size() == 0) {
    shift(l, r);
  }
  std::cout << r.Pop() << std::endl;
}
int front(Stack l, Stack r) {
  if(l.top == -1) {
    std::cout << "error" << std::endl;
  }
  if(r.stack_size() == 0) {
    shift(l, r);
    std::cout << r.Pop() << std::endl;
  }
  std::cout << r.Pop() << std::endl; 
  return 0;
}
int size(Stack l, Stack r) {
  std::cout << l.stack_size() + r.stack_size() << std::endl;
  return 0;
}
void clear(Stack l, Stack r) {
  l.top = -1;
  r.top = -1;
  l.low = 1;
  r.low = 1;  
}
int q_min(Stack l, Stack r) {
  if(l.top == -1) {
    std::cout << "error" << std::endl;
  }
  std::cout << (((l.stack_min()) < (r.stack_min())) ? (l.stack_min()) : (r.stack_min())) << std::endl;
  return 0;
}

int main() {
  Stack s1, s2;
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "enqueue") {
      std::cin >> num;
      enqueue(s1, s2, num);
    }
    if (cmd == "dequeue") {
      dequeue(s1, s2);
    }
    if (cmd == "front") {
      front(s1, s2);
    }
    if (cmd == "size") {
      size(s1, s2);
    }
    if (cmd == "clear") {
      clear(s1, s2);
    }
    if (cmd == "min") {
      q_min(s1, s2);
    }
    test--;
  }
  return 0;
}