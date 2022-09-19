#include <iostream>

int BinarySearch(const int* begin, const int* end) {
  int left = 0;
  int right = end - begin - 1;
  if (*(begin) == 1) {
    return 0;
  }
  while (left <= right) {
    int mid = (right + left) / 2;
    if (*(begin + mid - 1) > *(begin + mid)) {
      return mid;
    }
    if (*(begin + mid) > *(begin + mid + 1)) {
      return mid + 1;
    }
    if (*(begin + mid) > *(begin + right)) {
      left = mid + 1;
    }
    if (*(begin + mid) < *(begin + right)) {
      right = mid - 1;
    }
  }
}
int main() {
  int size;
  std::cin >> size;
  int* arr = new int[size];
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  std::cout << BinarySearch(arr, arr + size) << std::endl;
  delete[] arr;
  return 0;
}
