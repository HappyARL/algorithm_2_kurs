#include <iostream>

int const kLength = 1e5 + 5;
long long ans[kLength];

void Merge(std::pair<int, int>* arr, int start, int mid, int end) {
  int i = start, j = mid + 1, k = 0;
  std::pair<int, int> temp[kLength];
  while (i <= mid && j <= end) {
    if (arr[i].first > arr[j].first) {
      temp[k] = arr[i];
      ans[arr[i].second] += end - j + 1;
      i++;
    } else {
      temp[k] = arr[j];
      j++;
    }
    k++;
  }
  while (i <= mid) {
    temp[k] = arr[i];
    k++;
    i++;
  }
  while (j <= end) {
    temp[k] = arr[j];
    k++;
    j++;
  }
  for (int i = start; i <= end; i++) {
    arr[i] = temp[i - start];
  }
}

void MergeSort(std::pair<int, int>* arr, int start, int end) {
  if (start < end) {
    int mid = (start + end) / 2;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, start, mid, end);
  }
}

int main() {
  int par;
  std::cin >> par;
  std::pair<int, int> arr[par];
  for(int i = 0; i < par; i++) {
    std::cin >> arr[i].first >> arr[i].second;
  }
  MergeSort(arr, 0, par);
  
  return 0;
}