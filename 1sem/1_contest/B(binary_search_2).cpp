#include <iostream>

int BinarySearch(const int* begin, int size) {
  int left = 0;
  int right = size - 1;
  while (*(begin + left) >= *(begin + right)) {
    int mid = (left + right) / 2;
    if (*(begin + mid) == *(begin + left)) {
      return mid + 1;
    }
    if (*(begin + mid) < *(begin + mid - 1)) {
      return mid;
    }
    if (*(begin + mid) > *(begin + left)) {
      left = mid;
    } else {
      right = mid - 1;
    }
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
  std::cout << BinarySearch(arr, size) << std::endl;
  return 0;
}


/*

#include <iostream>

int BinarySearch(const int* begin, int left, int right) {
  int mid = (left + right) / 2;
  if (*(begin + mid) == *(begin + left)) {
    return mid + 1;
  }
  if (*(begin + left) < *(begin + right)) {
    return 0;
  }
  if (*(begin + mid) < *(begin + mid - 1)) {
    return mid;
  }
  if (*(begin + mid) > *(begin + left)) {
    return BinarySearch(begin, mid, right);
  }
  return BinarySearch(begin, left, mid - 1);
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
  std::cout << BinarySearch(arr, left, right) << std::endl;
  return 0;
}

}*/
