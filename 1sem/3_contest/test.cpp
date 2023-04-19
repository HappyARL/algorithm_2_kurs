#include <iostream>
#include <vector>

int main() {
  int q;
  std::cin >> q;
  std::vector<std::pair<std::string, std::string>> arr;
  for (int i = 0; i < q; ++i) {
    std::string word;
    std::string name;
    std::cin >> word >> name;
    arr.push_back({word, name});
  }
  for (int i = 0; i < 3; ++i) {
    std::cout << arr[i].first << " / " << arr[i].second << std::endl;
  }
  return 0;
}