#include <iostream>

int const kLength = 1e5 + 5;
long long ans[kLength];
std::pair<int, int> arr[kLength];

void Merge(int start, int mid, int end) {
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

void MergeSort(int start, int end) {
  if (start < end) {
    int mid = (start + end) / 2;
    MergeSort(start, mid);
    MergeSort(mid + 1, end);
    Merge(start, mid, end);
  }
}

int main() {
  int size;
  std::cin >> size;
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i].first;
    arr[i].second = i;
  }
  MergeSort(0, size - 1);
  for (int i = 0; i < size; i++) {
    std::cout << ans[i] << " ";
  }
  return 0;
}

/*
void Merge(int* arr, int start, int mid, int end) {
  int len1 = mid - start + 1, len2 = end - mid, i = 0, j = 0, k = start;
  int* left_arr = new int[len1];
  int* right_arr = new int[len2];
  for (int a = 0; a < len1; a++) {
    left_arr[a] = arr[start + a];
  }
  for (int b = 0; b < len2; b++) {
    right_arr[b] = arr[mid + 1 + b];
  }
  while (i < len1 && j < len2) {
    if (left_arr[i] <= right_arr[j]) {
      arr[k] = left_arr[i];
      i++;
    } else {
      arr[k] = right_arr[j];
      j++;
    }
    k++;
  }
  while (i < len1) {
    arr[k] = left_arr[i];
    i++;
    k++;
  }
  while (j < len2) {
    arr[k] = right_arr[j];
    j++;
    k++;
  }
  delete[] left_arr;
  delete[] right_arr;
}

void MergeSort(int* arr, int start, int end) {
  if (start < end) {
    int mid = start + (end - start) / 2;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, start, mid, end);
  }
}

*/