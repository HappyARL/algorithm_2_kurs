#include <iostream>
#include <vector>

void Swap(int* a, int* b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

void HeapifyMax(std::vector<int>& h_t, int i) {
  int size = h_t.size();
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < size && h_t[l] > h_t[largest]) {
    largest = l;
  }
  if (r < size && h_t[r] > h_t[largest]) {
    largest = r;
  }
  if (largest != i) {
    Swap(&h_t[i], &h_t[largest]);
    HeapifyMax(h_t, largest);
  }
}

void HeapifyMin(std::vector<int>& h_t, int i) {
  int size = h_t.size();
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < size && h_t[l] < h_t[largest]) {
    largest = l;
  }
  if (r < size && h_t[r] < h_t[largest]) {
    largest = r;
  }
  if (largest != i) {
    Swap(&h_t[i], &h_t[largest]);
    HeapifyMin(h_t, largest);
  }
}

void HeapMin(std::vector<int>& h_t) {
  int size = h_t.size();
  for (int i = size / 2 - 1; i >= 0; i--) {
    HeapifyMin(h_t, i);
  }
}

void HeapMax(std::vector<int>& h_t) {
  int size = h_t.size();
  for (int i = size / 2 - 1; i >= 0; i--) {
    HeapifyMax(h_t, i);
  }
}

void Insert(std::vector<int>& h_t, int num) {
  int size = h_t.size();
  if (size == 0) {
    h_t.push_back(num);
  } else {
    h_t.push_back(num);
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(h_t, i);
    }
  }
  std::cout << "ok" << std::endl;
}

void GetMin(std::vector<int>& h_t) {
  if (h_t.empty()) {
    std::cout << "error" << std::endl;
  } else {
    HeapMin(h_t);
    std::cout << h_t[0] << std::endl;
  }
}

void ExtractMin(std::vector<int>& h_t) {
  if (h_t.empty()) {
    std::cout << "error" << std::endl;
  }
  HeapMin(h_t);
  std::cout << h_t[0] << std::endl;
  int size = h_t.size();
  int i;
  for (i = 0; i < size; i++) {
    if (h_t[0] == h_t[i]) {
      break;
    }
  }
  Swap(&h_t[i], &h_t[size - 1]);
  h_t.pop_back();
  for (int i = size / 2 - 1; i >= 0; i--) {
    HeapifyMax(h_t, i);
  }
}

void GetMax(std::vector<int>& h_t) {
  if (h_t.empty()) {
    std::cout << "error" << std::endl;
  } else {
    HeapMax(h_t);
    std::cout << h_t[0] << std::endl;
  }
}

void ExtractMax(std::vector<int>& h_t) {
  if (h_t.empty()) {
    std::cout << "error" << std::endl;
  }
  HeapMax(h_t);
  std::cout << h_t[0] << std::endl;
  int size = h_t.size();
  int i;
  for (i = 0; i < size; i++) {
    if (h_t[0] == h_t[i]) {
      break;
    }
  }
  Swap(&h_t[i], &h_t[size - 1]);
  h_t.pop_back();
  for (int i = size / 2 - 1; i >= 0; i--) {
    HeapifyMax(h_t, i);
  }
}

void Clear(std::vector<int>& h_t) {
  h_t.clear();
  std::cout << "ok" << std::endl;
}

void Size(std::vector<int>& h_t) { std::cout << h_t.size() << std::endl; }

int main() {
  std::vector<int> h_t;
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      std::cin >> num;
      Insert(h_t, num);
    }
    if (cmd == "extract_min") {
      ExtractMin(h_t);
    }
    if (cmd == "get_min") {
      GetMin(h_t);
    }
    if (cmd == "extract_max") {
      ExtractMax(h_t);
    }
    if (cmd == "get_max") {
      GetMax(h_t);
    }
    if (cmd == "size") {
      Size(h_t);
    } else if (cmd == "clear") {
      Clear(h_t);
    }
  }
  return 0;
}