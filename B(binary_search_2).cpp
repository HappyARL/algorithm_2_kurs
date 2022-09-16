#include <iostream>

int BinarySearch(const int* begin, const int* end) {
  int left = 0;
  int right = end - begin - 1;
  while (*(begin + left) >= *(begin + right)) {
    int mid = (right + left) / 2;
    if (*(begin + right) == 1) {
      return right;
    }
    if (*(begin + left + mid) < *(begin + left + mid - 1) &&
        *(begin + left + mid) < *(begin + left + mid + 1)) {
      return left + mid;
    }
    left = --mid;
  }
  return 0;
}
int main() {
  int size;
  std::cin >> size;
  int arr[100000] = {};
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  std::cout << BinarySearch(arr, arr + size) << std::endl;
  return 0;
}
