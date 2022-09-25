#include <iostream>

int main() {
  int n, k;
  std::cin >> n >> k;
  int* arr = new int[n];
  std::cin >> arr[0] >> arr[1];
  for (int i = 2; i < k; i++) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10000000 + 4321);
  }
  std::cout << arr[k - 1] << std::endl;
  delete[] arr;
  return 0;
}
