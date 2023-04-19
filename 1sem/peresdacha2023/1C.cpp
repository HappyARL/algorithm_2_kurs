#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target) {
  int left = 0;
  int right = end - begin - 1;
  while (left <= right) {
    int mid = (right + left) / 2;
    if (*(begin + mid) == target) {
      return true;
    }
    if (*(begin + mid) < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return false;
}

int main() {
  int size, lumos;
  std::cin >> size >> lumos;
  int* arr = new int[size];
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
  
  delete[] arr;
  return 0;
}
