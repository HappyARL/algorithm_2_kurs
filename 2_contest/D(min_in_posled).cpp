#include <iostream>
#include <vector>

void Merge(std::vector<int> arr, int start, int mid, int end) {
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
      arr[k] = left_arr[i++];
    } else {
      arr[k] = right_arr[j++];
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

void MergeSort(std::vector<int> arr, int start, int end) {
  if (start < end) {
    int mid = start + (end - start) / 2;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, start, mid, end);
  }
}

int main() {
  int size, k, a0, x, y;
  std::cin >> size >> k;
  std::vector<int> arr;
  std::cin >> a0 >> x >> y;
  arr.push_back(a0);
  for (int i = 1; i <= size; i++) {
    int num = (x * arr[i - 1] + y);
    arr.push_back(num);
  }
  MergeSort(arr, 1, size);
  for (int i = 1; i <= k; i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}

/*
void Merge(std::vector<int> arr, int left, int right, int mid, int length) {
  int i = left, j = mid + 1, k = left;
  std::vector<int> temp = {0};
  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i];
      i++;
      k++;
    } else {
      j++;
      k++;
    }
  }
  while (i <= mid) {
    temp[k] = arr[i];
    i++;
    k++;
  }
  while (j <= right) {
    temp[k] = arr[j];
    j++;
    k++;
  }
  for (int p = 1; p <= length; p++) {
    arr[p] = temp[p];
  }
}
void MergeSort(std::vector<int> arr, int left, int right, int length) {
  if (left < right) {
    int mid = (left + right) / 2;
    MergeSort(arr, left, mid, length);
    MergeSort(arr, mid + 1, right, length);
    Merge(arr, left, right, mid, length);
  }
}

int main() {
  int size, k, a0, x, y;
  std::cin >> size >> k;
  std::vector<int> arr;
  std::cin >> a0 >> x >> y;
  arr.push_back(a0);
  for (int i = 1; i <= size; i++) {
    int num = (x * arr[i - 1] + y);
    arr.push_back(num);
  }
  MergeSort(arr, 1, size, size);
  for (int i = 1; i <= k; i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}

/////////////////////////////////////

void Merge(std::vector<int> arr, int start, int mid, int end) {
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

void MergeSort(std::vector<int> arr, int start, int end) {
  if (start < end) {
    int mid = start + (end - start) / 2;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, start, mid, end);
  }
}
*/