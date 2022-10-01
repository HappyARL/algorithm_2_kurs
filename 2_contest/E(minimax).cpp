#include <iostream>

class Heap {
 public:
  int heap_size = 0;
  int harr[100000] = {0};

  int Parent(int i) { return (i - 1) / 2; }
  int Left(int i) { return (2 * i + 1); }
  int Right(int i) { return (2 * i + 2); }
  void Swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
  }
  void Insert(int num) {
    heap_size++;
    int i = heap_size - 1;
    harr[i] = num;
    while (i != 0 && harr[Parent(i)] > harr[i]) {
      Swap(&harr[i], &harr[Parent(i)]);
      i = Parent(i);
    }
    std::cout << "ok" << std::endl;
  }
  void ExtractMin() {
    if(heap_size == 0) {
      std::cout << "error" << std::endl;
    }
    if (heap_size == 1) {
      heap_size--;
      std::cout << harr[0] << std::endl;
    }
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    std::cout << root << std::endl;
  }
  void GetMin() {
    if(heap_size == 0) {
      std::cout << "error" << std::endl;
    }
    std::cout << harr[0] << std::endl;
  }
  void ExtractMax() {
    std::cout << "none" << std::endl;
  }
  void GetMax() {
    std::cout << "none" << std::endl;
  }
  void Size() {
    std::cout << heap_size << std::endl;
  }
  void Clear() {
    harr[heap_size] = {0};
    heap_size = 0;
    std::cout << "ok" << std::endl;
  }
};

int main() {
  Heap h;
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      std::cin >> num;
      h.Insert(num);
    }
    if (cmd == "extract_min") {
      h.ExtractMin();
    }
    if (cmd == "get_min") {
      h.GetMin();
    }
    if (cmd == "extract_max") {
      h.ExtractMax();
    }
    if (cmd == "get_max") {
      h.GetMax();
    }
    if (cmd == "size") {
      h.Size();
    }
    if (cmd == "clear") {
      h.Clear();
    }
  }
  return 0;
}

/*#include <algorithm>
#include <iostream>
#include <string>

const int kLength = 2e5 + 5;

class Stack {
 public:
  int top = 0;
  int main_arr[kLength];
  int min_arr[kLength];
  int max_arr[kLength];

  void Insert(int val) {
    if (top == 0) {
      min_arr[top] = val;
    }
    top++;
    main_arr[top] = val;
    min_arr[top] = std::min(min_arr[top - 1], main_arr[top]);
    max_arr[top] = std::max(max_arr[top - 1], main_arr[top]);
    std::cout << "ok" << std::endl;
  }
  void ExtractMin() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      int extarct_value = min_arr[top];
      top--;
      std::cout << extarct_value << std::endl;
    }
  }
  void GetMin() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << min_arr[top] << std::endl;
    }
  }
  void ExtractMax() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      int extarct_value = max_arr[top];
      top--;
      std::cout << extarct_value << std::endl;
    }
  }
  void GetMax() {
    if (top == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << max_arr[top] << std::endl;
    }
  }
  void Size() { std::cout << top << std::endl; }
  void Clear() {
    top = 0;
    std::cout << "ok" << std::endl;
  }
};

int main() {
  Stack s1;
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      std::cin >> num;
      s1.Insert(num);
    }
    if (cmd == "extract_min") {
      s1.ExtractMin();
    }
    if (cmd == "get_min") {
      s1.GetMin();
    }
    if (cmd == "extract_max") {
      s1.ExtractMax();
    }
    if (cmd == "get_max") {
      s1.GetMax();
    }
    if (cmd == "size") {
      s1.Size();
    }
    if (cmd == "clear") {
      s1.Clear();
    }
  }
}*/
