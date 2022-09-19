#include <iostream>
#include <cmath>

const int kkLength = 10;

class Stack {
 public:
  int top;
  int main_arr[kkLength];
  int low_arr[kkLength];
  Stack() {
    top = 0;
    low_arr[0] = 1e9 + 9;
  }

  void Push(int val) {
    top++;
    main_arr[top] = val;
    low_arr[top] = std::min(low_arr[top - 1], main_arr[top]);
    std::cout << "ok " << top <<std::endl;
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

  int stack_size() {
    return top;
  }

  int stack_min() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      return low_arr[top];
    }
    return 0;
  }

  void stack_clear() {
    top = 0;
    std::cout << "ok" << std::endl;
  }
}st;

// +++++++++++++++++++++++++++++++++++++++++++++++
Stack l, r;

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
  if(l.top == 0) {
    std::cout << "error" << std::endl;
  }
  if(r.top == 0) {
    shift(l, r);
  }
  std::cout << r.Pop() << std::endl;
}
int front(Stack l, Stack r) {
  if(l.top == 0) {
    std::cout << "error" << std::endl;
  }
  if(r.stack_size() == 0) {
    shift(l, r);
    std::cout << r.Back() << std::endl;
  }
  std::cout << r.Back() << std::endl; 
  return 0;
}
int size(Stack l, Stack r) {
  std::cout << l.stack_size() + r.stack_size() << std::endl;
  return 0;
}
void clear(Stack l, Stack r) {
  l.stack_clear();
  r.stack_clear(); 
}
int min(Stack l, Stack r) {
  if(l.top == 0) {
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
      min(s1, s2);
    }
    test--;
  }
  return 0;
}


/*#include <iostream>
#include <cmath>

const int kkLength = 10;

class Stack {
 public:
  int top;
  int main_arr[kkLength];
  int low_arr[kkLength];
  Stack() {
    top = 0;
    low_arr[0] = 1e9 + 9;
  }

  void Push(int val) {
    top++;
    main_arr[top] = val;
    low_arr[top] = std::min(low_arr[top - 1], main_arr[top]);
    std::cout << "ok" << " " << top << std::endl;
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

  int stack_size() {
    return top;
  }

  int stack_min() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      return low_arr[top];
    }
    return 0;
  }

  void stack_clear() {
    top = 0;
    std::cout << "ok" << std::endl;
  }
};
//+++++++++++++++++++++++++++++++++++++++++
class Queue {
 public:
  Stack s1;
  Stack s2;

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
    if(l.top == 0) {
      std::cout << "error" << std::endl;
    }
    if(r.stack_size() == 0) {
      shift(l, r);
    }
    std::cout << r.Pop() << std::endl;
  }

  int front(Stack l, Stack r) {
    if(l.top == 0) {
      std::cout << "error" << std::endl;
    }
    if(r.stack_size() == 0) {
      shift(l, r);
    }
    std::cout << r.Back() << std::endl;
    return 0;
  }
  int size(Stack l, Stack r) {
    std::cout << l.stack_size() + r.stack_size() << std::endl;
    return 0;
  }
  void clear(Stack l, Stack r) {
    l.stack_clear();
    r.stack_clear(); 
  }
  int min(Stack l, Stack r) {
    if(l.top == 0) {
      std::cout << "error" << std::endl;
    }
    std::cout << (((l.stack_min()) < (r.stack_min())) ? (l.stack_min()) : (r.stack_min())) << std::endl;
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
      q.enqueue(q.s1, q.s2, num);
    }
    if (cmd == "dequeue") {
      q.dequeue(q.s1, q.s2);
    }
    if (cmd == "front") {
      q.front(q.s1, q.s2);
    }
    if (cmd == "size") {
      q.size(q.s1, q.s2);
    }
    if (cmd == "clear") {
      q.clear(q.s1, q.s2);
    }
    if (cmd == "min") {
      q.min(q.s1, q.s2);
    }
    test--;
  }
  return 0;
}*/