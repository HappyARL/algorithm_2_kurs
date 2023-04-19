#include <iostream>
#include <vector>

std::vector<int> MPP(std::vector<int> arr, int length) {
  std::vector<int> vec;
  vec.push_back(arr[0]);
  for (int i = 1; i < length; ++i) {
    if (arr[0] < arr[i]) {
      vec.push_back(arr[i]);
    }
    
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> arr;
  for (int i = 0; i < n; ++i) {
    int num;
    std::cin >> num;
    arr.push_back(num);
  }
  std::vector<int> ans = MPP(arr, n);
  std::cout << ans.size() << std::endl;
  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << " ";
  }
  return 0;
}