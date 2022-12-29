#include <iostream>
#include <vector>

std::vector<int> PutItem(const int* weight, int* price, int item, int ruczak) {
  int** a = new int*[item + 1];
  for (int i = 0; i < item + 1; ++i) {
    a[i] = new int[ruczak + 1];
  }
  for (int i = 0; i <= item; ++i) {
    a[i][0] = 0;
  }
  for (int i = 0; i <= ruczak; ++i) {
    a[0][i] = 0;
  }
  for (int i = 1; i <= item; ++i) {
    for (int j = 1; j <= ruczak; ++j) {
      if (j < weight[i]) {
        a[i][j] = a[i - 1][j];
      } else {
        a[i][j] = std::max(a[i - 1][j], a[i - 1][j - weight[i]] + price[i]);
      }
    }
  }
  int i = item;
  int j = ruczak;
  std::vector<int> vec;
  while (i != 0) {
    if (a[i][j] != a[i - 1][j]) {
      vec.push_back(i);
      j -= weight[i];
      --i;
    } else {
      --i;
    }
  }
  for (int i = 0; i < item + 1; ++i) {
    delete[] a[i];
  }
  delete[] a;
  return vec;
}

int main() {
  int item, ruczak;
  std::cin >> item >> ruczak;
  int* weight = new int[item + 1];
  int* price = new int[item + 1];
  weight[0] = 0;
  for (int i = 1; i <= item; ++i) {
    std::cin >> weight[i];
  }
  price[0] = 0;
  for (int i = 1; i <= item; ++i) {
    std::cin >> price[i];
  }
  std::vector<int> ans = PutItem(weight, price, item, ruczak);
  for (int i = (int)ans.size() - 1; i >= 0; --i) {
    std::cout << ans[i] << std::endl;
  }
  delete[] weight;
  delete[] price;
  return 0;
}