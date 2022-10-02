#include <iostream>

class BinaryHeap {
 public:
  int* harr;
  int capacity;
  int heap_size;
  int* heap_count;
  BinaryHeap() {
    capacity = 100000;
    heap_size = 0;
    harr = new int[capacity];
    heap_count = new int[capacity];
  }
  int Parent(int i) { return (i - 1) / 2; }
  int Left(int i) { return (2 * i + 1); }
  int Right(int i) { return (2 * i + 2); }
  void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
  }
  void Insert(int num, int num_cmd) {
    heap_size++;
    int i = heap_size - 1;
    harr[i] = num;
    heap_count[i] = num_cmd;
    while (i != 0 && harr[Parent(i)] > harr[i]) {
      swap(&harr[i], &harr[Parent(i)]);
      i = Parent(i);
    }
  }
  void Min() {
    std::cout << harr[0] << std::endl;
  }
  int ExtractMin() {
    if (heap_size == 1) {
      heap_size--;
      return harr[0];
    }
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    return root;
  }
  void Decrease(int l, int d) {
    int i = 0;
    while (heap_count[i] != l) {
      i++;
    }
    harr[i] -= d;
    while (i != 0 && harr[Parent(i)] > harr[i]) {
      swap(&harr[i], &harr[Parent(i)]);
      i = Parent(i);
    }
  }
};

int main() {
  BinaryHeap heap;
  int check, num, dcrs, line, num_cmd = 1;
  std::cin >> check;
  while (check != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      std::cin >> num;
      heap.Insert(num, num_cmd);
    }
    if (cmd == "getMin") {
      heap.Min();
    }
    if (cmd == "extractMin") {
      heap.ExtractMin();
    }
    if (cmd == "decreaseKey") {
      std::cin >> line >> dcrs;
      heap.Decrease(line, dcrs);
    }
    num_cmd++;
    --check;
  }
  delete[] heap.harr;
  delete[] heap.heap_count;
  return 0;
}