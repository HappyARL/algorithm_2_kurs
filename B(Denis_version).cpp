#include <iostream>

int BinarySearch(int* arr, int left, int right, int mid) {
  if (arr[left] < arr[right]) {
    return 0;
  }
  if (arr[mid] < arr[mid - 1]) {
    return mid;
  }
  if (arr[mid] > arr[mid + 1]) {
    return mid + 1;
  }
  if (arr[left] > arr[mid]) {
    BinarySearch(arr, left, mid, (mid + left) / 2);
  }
  return BinarySearch(arr, mid, right, (mid + right) / 2);
}
int main() {
  int size;
  std::cin >> size;
  int arr[100000] = {};
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  int left = 0;
  int right = size - 1;
  int mid = (left + right) / 2;
  std::cout << BinarySearch(arr, left, right, mid) << std::endl;
  return 0;
}
