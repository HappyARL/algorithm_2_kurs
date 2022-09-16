#include <iostream>

int BinarySearch(const int* begin, const int* end, int mid) {
  if (*(begin) < *(end)) {
    return 0;
  }
  if (*(begin + mid) < *(begin + mid - 1)) {
    return mid;
  }
  if (*(begin + mid) > *(begin + mid + 1)) {
    return mid + 1;
  }
  if (*begin > mid) {
    BinarySearch(begin, begin + mid, mid / 2);
  }
  return BinarySearch(begin + mid, end, (mid + (end - begin)) / 2);
}
int main() {
  int size;
  std::cin >> size;
  int arr[100000] = {};
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  int mid_num = (size - 1) / 2;
  std::cout << BinarySearch(arr, arr + size - 1, mid_num) << std::endl;
  return 0;
}
