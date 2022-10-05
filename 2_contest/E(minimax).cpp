#include <iostream>
#include <vector>

std::vector<int> arr;

void HeapifyMax(int i) {
  int size = arr.size();
  int largest = i;
  if (2 * i + 1 < size && arr[2 * i + 1] > arr[largest]) {
    largest = 2 * i + 1;
  }
  if (2 * i + 2 < size && arr[2 * i + 2] > arr[largest]) {
    largest = 2 * i + 2;
  }
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    HeapifyMax(largest);
  }
}

void HeapifyMin(int i) {
  int size = arr.size();
  int largest = i;
  if (2 * i + 1 < size && arr[2 * i + 1] < arr[largest]) {
    largest = 2 * i + 1;
  }
  if (2 * i + 2 < size && arr[2 * i + 2] < arr[largest]) {
    largest = 2 * i + 2;
  }
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    HeapifyMin(largest);
  }
}

void Insert(int num) {
  int size = arr.size();
  if (size == 0) {
    arr.push_back(num);
  } else {
    arr.push_back(num);
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(i);
    }
  }
  std::cout << "ok" << std::endl;
}

void GetMin() {
  if (arr.empty()) {
    std::cout << "error" << std::endl;
  } else {
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMin(i);
    }
    std::cout << arr[0] << std::endl;
  }
}

void ExtractMin() {
  if (arr.empty()) {
    std::cout << "error" << std::endl;
  } else {
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMin(i);
    }
    std::cout << arr[0] << std::endl;
    int i;
    for (i = 0; i < size; i++) {
      if (arr[0] == arr[i]) {
        break;
      }
    }
    std::swap(arr[i], arr[size - 1]);
    arr.pop_back();
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(i);
    }
  }
}

void GetMax() {
  if (arr.empty()) {
    std::cout << "error" << std::endl;
  } else {
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(i);
    }
    std::cout << arr[0] << std::endl;
  }
}

void ExtractMax() {
  if (arr.empty()) {
    std::cout << "error" << std::endl;
  } else {
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(i);
    }
    std::cout << arr[0] << std::endl;
    int i;
    for (i = 0; i < size; i++) {
      if (arr[0] == arr[i]) {
        break;
      }
    }
    std::swap(arr[i], arr[size - 1]);
    arr.pop_back();
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(i);
    }
  }
}

void Clear() {
  arr.clear();
  std::cout << "ok" << std::endl;
}

void Size() { std::cout << arr.size() << std::endl; }

int main() {
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      std::cin >> num;
      Insert(num);
    } else if (cmd == "extract_min") {
      ExtractMin();
    } else if (cmd == "get_min") {
      GetMin();
    } else if (cmd == "extract_max") {
      ExtractMax();
    } else if (cmd == "get_max") {
      GetMax();
    } else if (cmd == "size") {
      Size();
    } else if (cmd == "clear") {
      Clear();
    }
    --test;
  }
  return 0;
}

/*
#include <iostream>
#include <vector>

std::vector<int> heap_min;
std::vector<int> heap_max;

void HeapifyMax(int i) {
  int size = heap_max.size();
  int largest = i;
  if (2 * i + 1 < size && heap_max[2 * i + 1] > heap_max[largest]) {
    largest = 2 * i + 1;
  }
  if (2 * i + 2 < size && heap_max[2 * i + 2] > heap_max[largest]) {
    largest = 2 * i + 2;
  }
  if (largest != i) {
    std::swap(heap_max[i], heap_max[largest]);
    HeapifyMax(largest);
  }
}

void HeapifyMin(int i) {
  int size = heap_min.size();
  int largest = i;
  if (2 * i + 1 < size && heap_min[2 * i + 1] < heap_min[largest]) {
    largest = 2 * i + 1;
  }
  if (2 * i + 2 < size && heap_min[2 * i + 2] < heap_min[largest]) {
    largest = 2 * i + 2;
  }
  if (largest != i) {
    std::swap(heap_min[i], heap_min[largest]);
    HeapifyMin(largest);
  }
}

void Insert(int num) {
  int size = heap_max.size();
  if (size == 0) {
    heap_max.push_back(num);
    heap_min.push_back(num);
  } else {
    heap_max.push_back(num);
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(i);
    }
    heap_min.push_back(num);
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMin(i);
    }
  }
  std::cout << "ok" << std::endl;
}

void GetMin() {
  if (heap_min.empty()) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << heap_min[0] << std::endl;
  }
}

  void ExtractMin() {
    if (heap_min.empty()) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << heap_min[0] << std::endl;
      int i, save = heap_min[0], size = heap_min.size();
      for (i = 0; i < size; i++) {
        if (heap_min[0] == heap_min[i]) {
          break;
        }
      }
      std::swap(heap_min[i], heap_min[size - 1]);
      heap_min.pop_back();
      for (int i = size / 2 - 1; i >= 0; i--) {
        HeapifyMin(i);
      }
      for(int i = 0; i < size; i++) {
        if(heap_max[i] == save) {
          std::swap(heap_max[i], heap_max[size - 1]);
           heap_max.pop_back();
           for (int i = size / 2 - 1; i >= 0; i--) {
            HeapifyMax(i);
          }
        } 
      }
    }
  }

  void GetMax() {
    if (heap_max.empty()) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << heap_max[0] << std::endl;
    }
  }

  void ExtractMax() {
    if (heap_max.empty()) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << heap_max[0] << std::endl;
      int i, save = heap_max[0], size = heap_max.size();
      for (i = 0; i < size; i++) {
        if (heap_max[0] == heap_max[i]) {
          break;
        }
      }
      std::swap(heap_max[i], heap_max[size - 1]);
      heap_max.pop_back();
      for (int i = size / 2 - 1; i >= 0; i--) {
        HeapifyMax(i);
      }
      for(int i = 0; i < size; i++) {
        if(heap_min[i] == save) {
          std::swap(heap_min[i], heap_min[size - 1]);
           heap_min.pop_back();
           for (int i = size / 2 - 1; i >= 0; i--) {
            HeapifyMin(i);
          }
        } 
      }
    }
  }

  void Clear() {
    heap_min.clear();
    heap_max.clear();
    std::cout << "ok" << std::endl;
  }

  void Size() { std::cout << heap_max.size() << std::endl; }


int main() {
  int test, num;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      std::cin >> num;
      Insert(num);
    } else if (cmd == "extract_min") {
      ExtractMin();
    } else if (cmd == "get_min") {
      GetMin();
    } else if (cmd == "extract_max") {
      ExtractMax();
    } else if (cmd == "get_max") {
      GetMax();
    } else if (cmd == "size") {
      Size();
    } else if (cmd == "clear") {
      Clear();
    }
    --test;
  }
  return 0;
}
///////////////////////////////////////////
#include <iostream>
#include <vector>

class Heap {
 public:
  std::pair<int, int> heap_min;
  std::pair<int, int> heap_max;
  std::pair<int, int> pos;
  int size_max = 0;
  int size_min = 0;

  void ShiftUpMin() {
    int i = heap_min.size() - 1;
    while (i > 0) {
      int j = (i - 1) / 2;
      if (heap_min[i] > heap_min[j]) {
        std::swap(heap_min[i], heap_min[j]);
        i = j;
      } else {
        break;
      }
    }
  }

  void ShiftDownMin() {
    int i = 0, size = heap_min.size();
    while (i < size) {
      int son1 = (2 * i + 1 < size ? 2 * i + 1 : i);
      int son2 = (2 * i + 2 < size ? 2 * i + 2 : i);
      if (heap_min[i] < std::max(heap_min[son1], heap_min[son2])) {
        if (heap_min[son1] >= heap_min[son2]) {
          std::swap(heap_min[i], heap_min[son1]);
          i = son1;
        } else {
          std::swap(heap_min[i], heap_min[son2]);
          i = son2;
        }
      } else {
        break;
      }
    }
  }

  void ShiftUpMax() {
    int i = heap_max.size() - 1;
    while (i > 0) {
      int j = (i - 1) / 2;
      if (heap_max[i] > heap_max[j]) {
        std::swap(heap_max[i], heap_max[j]);
        i = j;
      } else {
        break;
      }
    }
  }

  void ShiftDownMax() {
    int i = 0, size = heap_max.size();
    while (i < size) {
      int son1 = (2 * i + 1 < size ? 2 * i + 1 : i);
      int son2 = (2 * i + 2 < size ? 2 * i + 2 : i);
      if (heap_max[i] < std::max(heap_max[son1], heap_max[son2])) {
        if (heap_max[son1] >= heap_max[son2]) {
          std::swap(heap_max[i], heap_max[son1]);
          i = son1;
        } else {
          std::swap(heap_max[i], heap_max[son2]);
          i = son2;
        }
      } else {
        break;
      }
    }
  }

  void Insert(int num) {
    if (size_max == 0) {
      heap_min[size_max++].first = a;
      ShiftUpMin();
      heap_max[size++] = a;
      ShiftUpMax();
    } else {
      std::swap(heap[0], heap[--size]);
      ShiftDown();
      heap[size++] = a;
      ShiftUp();
    }
  }

  void GetMin();
  void ExtractMin();
  void GetMax();
  void ExtractMax() {
    if (size_max == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << heap_max[0].first << "\n";
    int ind_min = pos[heap_max[0].second].first;
    size_max--;
    std::swap(pos[heap_max[0].second].second, pos[heap_max[size_max].second].second);
    std::swap(heap_max[0], heap_max[size_max]); int ind = heap_max[0].second;
    pos[ind].second = ShiftDownMax(0);
    size_min--;
    std::swap(pos[heap_min[ind_min].second].first, pos[heap_min[size_min].second].first);
    std::swap(heap_min[ind_min], heap_min[size_min]);
    ind = heap_min[ind_min].second;
    if (heap_min[ind_min].first < heap_min[(ind_min - 1) / 2].first) {
      pos[ind].first = ShiftUpMin(ind_min);
    } else {
      pos[ind].first = ShiftDownMin(ind_min);
  }
}
  void Size();
  void Clear();
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
    } else if (cmd == "extract_min") {
      h.ExtractMin();
    } else if (cmd == "get_min") {
      h.GetMin();
    } else if (cmd == "extract_max") {
      h.ExtractMax();
    } else if (cmd == "get_max") {
      h.GetMax();
    } else if (cmd == "size") {
      h.Size();
    } else if (cmd == "clear") {
      h.Clear();
    }
    --test;
  }
  return 0;
}
*/