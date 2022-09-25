#include <iostream>

int Compare(const void* x1, const void* x2) { return (*(int*)x1 - *(int*)x2); }

int main() {
  int n, k, x, y;
  std::cin >> n >> k;
  int* arr = new int[n];
  std::cin >> arr[0] >> x >> y;
  for (int i = 1; i <= n; i++) {
    arr[i] = (x * arr[i - 1] + y);
  }
  qsort(arr, n, sizeof(int), Compare);
  for (int i = 1; i <= k; i++) {
    std::cout << arr[i] << ' ';
  }
  delete[] arr;
  return 0;
}
