#include <iostream>
#include <vector>

int Partition(std::vector<int>& arr, int l, int r) {
  if (l != r) {
    std::swap(arr[l + rand() % (r - l)], arr[r]);
  }
  int x = arr[r];
  int i = l - 1;
  for (int j = l; j <= r; j++) {
    if (arr[j] <= x) {
      std::swap(arr[++i], arr[j]);
    }
  }
  return i;
}

int Stat(std::vector<int> arr, int n) {
  int l = 0, r = arr.size() - 1;
  for (;;) {
    int pos = Partition(arr, l, r);
    if (pos < n) {
      l = pos + 1;
    } else if (pos > n) {
      r = pos - 1;
    } else {
      return arr[n];
    }
  }
}

int main() {
  int n, k, a0, a1;
  std::cin >> n >> k;
  std::vector<int> arr;
  std::cin >> a0 >> a1;
  arr.push_back(a0);
  arr.push_back(a1);
  for (int i = 2; i < n; i++) {
    int num = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10000000 + 4321);
    arr.push_back(num);
  }
  std::cout << Stat(arr, k - 1) << std::endl;
  return 0;
}

 /*
int Statistics(std::std::vector<int> arr, int l, int r, int k) {
  if (l >= r) {
    return arr[l];
  }
  int i = l, j = r, p = arr[(l + r) / 2];
  while (i < j) {
    while (arr[i] < p) {
      i++;
    }
    while (arr[j] > p) {
      j--;
    }
    if (i < j) {
      int num = arr[j];
      arr[j] = arr[i];
      arr[i] = num;
      i++;
      j--;
    }
  }
  if (k >= l && k < i) {
    return Statistics(arr, l, i - 1, k);
  }
  if (j < k && k <= r) {
    return Statistics(arr, j + 1, r, k);
  }
  return p;
}
 */ 