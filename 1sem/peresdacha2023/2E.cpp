#include <iostream>
#include <vector>

class Minimax {
 private:
  std::vector<std::pair<long long, long long> > heap_;
  long long heap_size_;

 public:
  Minimax();
  ~Minimax();
  void Heapify(long long index);
  void ShiftUp(long long index);
  void ShiftDown(long long index);
  long long Parent(long long index);
  long long Left(long long index);
  long long Right(long long index);
  void Insert(long long value);
  void GetMin();
  void ExtractMin();
  void GetMax();
  void ExtractMax();
  void Size();
  void Clear();
};

Minimax::Minimax() {
  heap_size_ = 0;
  heap_ = std::vector<std::pair<long long, long long> >();
}

Minimax::~Minimax() {}

void Minimax::Heapify(long long index) {
  while (index != 0 && heap_[Parent(index)].first > heap_[index].first) {
    std::swap(heap_[index].first, heap_[Parent(index)].first);
    index = Parent(index);
  }
  long long maxIndex = index;
  if (Left(index) < heap_size_ && heap_[Left(index)].second > heap_[maxIndex].second) {
    maxIndex = Left(index);
  }
  if (Right(index) < heap_size_ && heap_[Right(index)].second > heap_[maxIndex].second) {
    maxIndex = Right(index);
  }
  if (index != maxIndex) {
    std::swap(heap_[index].second, heap_[maxIndex].second);
    Heapify(maxIndex);
  }
}
/*
void Minimax::ShiftUp(long long index) {
  while (index != 0 && heap_[Parent(index)].first > heap_[index].first) {
    std::swap(heap_[index].first, heap_[Parent(index)].first);
    index = Parent(index);
  }
  
}

void Minimax::ShiftDown(long long index) {
  while ((Left(index) < heap_size_ &&
          heap_[Left(index)].second < heap_[index].second) ||
         (Right(index) < heap_size_ &&
          heap_[Right(index)].second < heap_[index].second)) {
    if (Right(index) < heap_size_ &&
        heap_[Right(index)].second < heap_[Left(index)].second) {
      std::swap(heap_[index].second, heap_[Right(index)].second);
      index = Right(index);
    } else {
      std::swap(heap_[index].second, heap_[Left(index)].second);
      index = Left(index);
    }
  }
}*/

long long Minimax::Parent(long long index) { return (index - 1) / 2; }

long long Minimax::Left(long long index) { return (2 * index + 1); }

long long Minimax::Right(long long index) { return (2 * index + 2); }

void Minimax::Insert(long long value) {
  heap_size_++;
  long long i = heap_size_ - 1;
  heap_.push_back(std::pair<long long, long long>(value, value));
  std::cout << "ok" << std::endl;
  Heapify(i);
}

void Minimax::GetMin() { 
  if (heap_size_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << heap_[0].first << std::endl;
  }
}

void Minimax::ExtractMin() {
  if (heap_size_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << heap_[0].first << std::endl;
    heap_[0] = heap_[heap_size_ - 1];
    heap_size_--;
    heap_.pop_back();
    Heapify(0);
  }
}

void Minimax::GetMax() {
  if (heap_size_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << heap_[0].second << std::endl;
  }
}

void Minimax::ExtractMax() {
  if (heap_size_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    std::cout << heap_[0].second << std::endl;
    heap_[0] = heap_[heap_size_ - 1];
    heap_size_--;
    heap_.pop_back();
    Heapify(0);
  }
}

void Minimax::Size() { std::cout << heap_size_ << std::endl;}

void Minimax::Clear() {
  heap_.clear();
  std::cout << "ok" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Minimax heap;
  long long test;
  std::cin >> test;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      long long value;
      std::cin >> value;
      heap.Insert(value);
    } else if (cmd == "get_min") {
      heap.GetMin();
    } else if (cmd == "extract_min") {
      heap.ExtractMin();
    } else if (cmd == "get_max") {
      heap.GetMax();
    } else if (cmd == "extract_max") {
      heap.ExtractMax();
    } else if (cmd == "size") {
      heap.Size();
    } else if (cmd == "clear") {
      heap.Clear();
    }
    --test;
  }
  return 0;
}
