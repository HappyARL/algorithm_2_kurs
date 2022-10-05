#include <iostream>
#include <vector>

int Partition(std::vector<int>& arr, int start, int end) {
  int x = arr[start];
  int i = start, j;
  for (j = start + 1; j < end; j++) {
    if (arr[j] <= x) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i], arr[start]);
  return i;
}

void QuickSort(std::vector<int>& arr, int start, int end) {
  int r;
  if (start < end) {
    r = Partition(arr, start, end);
    QuickSort(arr, start, r);
    QuickSort(arr, r + 1, end);
  }
}

int main() {
  int i = 0, length, num;
  std::cin >> length;
  std::vector<int> arr;
  while (i != length) {
    std::cin >> num;
    arr.push_back(num);
    i++;
  }
  QuickSort(arr, 0, length);
  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}
