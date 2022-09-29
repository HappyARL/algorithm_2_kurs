#include <iostream>
#include <vector>

int Statistics(std::vector<int> arr, int l, int r, int k) {
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
  std::cout << Statistics(arr, 0, n - 1, k - 1) << std::endl;
  return 0;
}

/*#include <iostream>

int Compare(const void* x1, const void* x2) { return (*(int*)x1 - *(int*)x2); }

int main() {
  int n, k;
  std::cin >> n >> k;
  int* arr = new int[n];
  std::cin >> arr[0] >> arr[1];
  for (int i = 2; i < n; i++) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10000000 + 4321);
  }
  qsort(arr, n, sizeof(int), Compare);
  std::cout << arr[k - 1] << std::endl;
  delete[] arr;
  return 0;
}
*/

