#include <iostream>
#include <vector>

class BinaryHeap {
 private:
  std::vector<std::pair<long long, long long> > heap_;
  long long heap_size_;

 public:
  BinaryHeap();
  ~BinaryHeap();
  void ShiftUp(long long index);
  void ShiftDown(long long index);
  long long Parent(long long index);
  long long Left(long long index);
  long long Right(long long index);
  void Insert(long long value, long long order);
  void GetMin();
  void ExtractMin();
  void DecreaseKey(long long position, long long decrease_value);
};

BinaryHeap::BinaryHeap() {
  heap_size_ = 0;
  heap_ = std::vector<std::pair<long long, long long> >();
}

BinaryHeap::~BinaryHeap() {}

void BinaryHeap::ShiftUp(long long index) {
  while (index != 0 && heap_[Parent(index)].first > heap_[index].first) {
    std::swap(heap_[index], heap_[Parent(index)]);
    index = Parent(index);
  }
}

void BinaryHeap::ShiftDown(long long index) {
  while ((Left(index) < heap_size_ &&
          heap_[Left(index)].first < heap_[index].first) ||
         (Right(index) < heap_size_ &&
          heap_[Right(index)].first < heap_[index].first)) {
    if (Right(index) < heap_size_ &&
        heap_[Right(index)].first < heap_[Left(index)].first) {
      std::swap(heap_[index], heap_[Right(index)]);
      index = Right(index);
    } else {
      std::swap(heap_[index], heap_[Left(index)]);
      index = Left(index);
    }
  }
}

long long BinaryHeap::Parent(long long index) { return (index - 1) / 2; }

long long BinaryHeap::Left(long long index) { return (2 * index + 1); }

long long BinaryHeap::Right(long long index) { return (2 * index + 2); }

void BinaryHeap::Insert(long long value, long long order) {
  heap_size_++;
  long long i = heap_size_ - 1;
  heap_.push_back(std::pair<long long, long long>(value, order));
  ShiftUp(i);
}

void BinaryHeap::GetMin() { std::cout << heap_[0].first << std::endl; }

void BinaryHeap::ExtractMin() {
  heap_[0] = heap_[heap_size_ - 1];
  heap_size_--;
  heap_.pop_back();
  ShiftDown(0);
}

void BinaryHeap::DecreaseKey(long long position, long long decrease_value) {
  long long i = 0;
  while (heap_[i].second != position) {
    i++;
  }
  heap_[i].first -= decrease_value;
  ShiftUp(i);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  BinaryHeap heap;
  long long test;
  std::cin >> test;
  long long order = 1;
  while (test != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "insert") {
      long long value;
      std::cin >> value;
      heap.Insert(value, order);
    }
    if (cmd == "getMin") {
      heap.GetMin();
    }
    if (cmd == "extractMin") {
      heap.ExtractMin();
    }
    if (cmd == "decreaseKey") {
      long long position, decrease_value;
      std::cin >> position >> decrease_value;
      heap.DecreaseKey(position, decrease_value);
    }
    order++;
    --test;
  }
  return 0;
}
