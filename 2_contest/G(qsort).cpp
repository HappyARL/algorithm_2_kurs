#include <iostream>

int Compare(const void* x1, const void* x2) { return (*(int*)x1 - *(int*)x2); }

int main() {
  int i = 0, length;
  std::cin >> length;
  int* arr = new int[length];
  while (i != length) {
    std::cin >> arr[i];
    i++;
  }
  qsort(arr, length, sizeof(int), Compare);
  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << ' ';
  }
  delete[] arr;
  return 0;
}
