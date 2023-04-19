#include <iostream>
#include <vector>

int LIS(std::vector<int>& arr) {
  std::vector<int> ans;
  int n = arr.size();
  for (int i = 0; i < n; i++) {
    auto it = lower_bound(ans.begin(), ans.end(), arr[i]);
    if (it == ans.end()) {
      ans.push_back(arr[i]);
    } else {
      *it = arr[i];
    }
  }
  return ans.size();
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> vec;
  while (n != 0) {
    int num;
    std::cin >> num;
    vec.push_back(num);
    --n;
  }
  std::cout << LIS(vec) << std::endl;
  return 0;
}
