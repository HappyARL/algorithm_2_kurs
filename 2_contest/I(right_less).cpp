#include <iostream>

int main() {
  int size;
  std::cin >> size;
  int* arr = new int[size];
  int* b_arr = new int[size];
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  for (int i = 0; i < size; i++) {
    int count = -1;
    for (int j = i + 1; j <= size; j++) {
      if (arr[i] > arr[j]) {
        count++;
      }
      b_arr[i] = count;
    }
  }
  for (int i = 0; i < size; i++) {
    std::cout << b_arr[i] << " ";
  }
  delete[] arr;
  delete[] b_arr;
  return 0;
}