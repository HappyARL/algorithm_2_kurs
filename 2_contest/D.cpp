#include <iostream>
#include <vector>

void QuickSort(std::vector<size_t>& arr, size_t start, size_t finish) {
  if (start == finish) {
    return;
  }
  size_t begin = start;
  size_t last = finish;
  size_t mid = arr[(start + finish) / 2];
  while (begin <= last) {
    while (begin <= finish && arr[begin] < mid) {
      ++begin;
    }
    while (last >= start && arr[last] > mid) {
      --last;
    }
    if (begin <= last) {
      std::swap(arr[begin], arr[last]);
      ++begin;
      --last;
    }
  }
  if (begin < finish) {
    QuickSort(arr, begin, finish);
  }
  if (last > start) {
    QuickSort(arr, start, last);
  }
}

int main() {
  size_t n, k;
  std::cin >> n >> k; 
  size_t a, x, y;
  std::cin >> a >> x >> y;
  std::vector<size_t> arr;
  arr.push_back(a);
  for (size_t i = 1; i < n + 1; ++i) {
    arr.push_back(x * arr[i - 1] + y);
  }
  QuickSort(arr, (size_t)0, n + (size_t)1);
  for (size_t i = 1; i < k + 1; ++i) {
    std::cout << arr[i] << " ";
  }
  return 0;
}