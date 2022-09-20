#include <iostream>

class Stack {
 public:
  int top;
  int main_arr[100000];
  int low_arr[100000];
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

  int Size() { return top; }

  int Min() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      return low_arr[top];
    }
    return 0;
  }

  void Clear() {
    top = 0;
    std::cout << "ok" << std::endl;
  }
};

bool Check(char c, Stack* r) {
  bool result;
  if (c == ']') {
    result = r->Back() == '[';
  } else if (c == '}') {
    result = r->Back() == '{';
  } else {
    result = r->Back() == '(';
  }
  return result;
}

int main() {
  Stack st;
  std::string sp;
  std::cin >> sp;
  for (long unsigned int i = 0; i < sp.length(); i++) {
    if (sp[i] == '[' || sp[i] == '(' || sp[i] == '{') {
      st.Push(sp[i]);
    } else if (Check(sp[i], &st)) {
      st.Pop();
    } else {
      std::cout << "NO";
      return 0;
    }
  }
  if (st.Size() != 0) {
    std::cout << "NO" << std::endl;
  } else {
    std::cout << "YES" << std::endl;
  }
  return 0;
}
