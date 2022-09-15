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
  int size;
  std::cin >> size;
  int arr[100000];
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  int test;
  std::cin >> test;
  while (test != 0) {
    int begin, end, target;
    std::cin >> begin >> end >> target;
    bool ans = BinarySearch(arr + begin, arr + end, target);
    if (ans) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
    test--;
  }
  return 0;
}
