/*
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

void QuickQuickSort(std::vector<int>& arr, int start, int end) {
  int r;
  if (start < end) {
    r = Partition(arr, start, end);
    QuickQuickSort(arr, start, r);
    QuickQuickSort(arr, r + 1, end);
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
  QuickQuickSort(arr, 0, length);
  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}
*/

#include <iostream>
#include <vector>

const int kLength = 1e5 + 5;

void QuickSort(std::vector<int>& arr, int start, int end) {
  if (start == end) {
    return;
  }
  int i = start, j = end;
  int mid = arr[(start + end) / 2];
  while (i <= j) {
    while (i <= end && arr[i] < mid) {
      i++;
    }
    while (j >= start && arr[j] > mid) {
      j--;
    }
    if (i <= j) {
      std::swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }
  if (i < end) {
    QuickSort(arr, i, end);
  }
  if (j > start) {
    QuickSort(arr, start, j);
  }
}

int main() {
  int length, num;
  std::cin >> length;
  std::vector<int> arr;
  for (int i = 0; i < length; i++) {
    std::cin >> num;
    arr.push_back(num);
  }
  QuickSort(arr, 0, length - 1);
  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << " ";
  }
}
