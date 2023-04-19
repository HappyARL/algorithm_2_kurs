#include <iostream>
#include <vector>

void LSD(int64_t* arr, int length) {
  int64_t longest = arr[0];
  for (int i = 1; i < length; ++i) {
    if (arr[i] > longest) {
      longest = arr[i];
    }
  }
  for (int64_t rank = 1; longest / rank > 0; rank *= 10) {
    int64_t* result = new int64_t[length];
    int count[10] = {0};
    for (int i = 0; i < length; ++i) {
      count[(arr[i] / rank) % 10]++;
    }
    int prefix[10] = {0};
    prefix[0] = count[0];
    for (int i = 1; i < 10; ++i) {
      prefix[i] = prefix[i - 1] + count[i];
    }
    for (int i = length - 1; i >= 0; --i) {
      int digit = (arr[i] / rank) % 10;
      result[prefix[digit] - 1] = arr[i];
      prefix[digit]--;
    }
    for (int i = 0; i < length; ++i) {
      arr[i] = result[i];
    }
    delete[] result;
  }
  for (int i = 0; i < length; ++i) {
    std::cout << arr[i] << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int length;
  std::cin >> length;
  int64_t* arr = new int64_t[length];
  for (int i = 0; i < length; ++i) {
    std::cin >> arr[i];
  }
  LSD(arr, length);
  delete[] arr;
  return 0;
}
