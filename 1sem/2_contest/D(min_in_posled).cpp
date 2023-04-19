#include <algorithm>
#include <iostream>
#include <vector>

int size;
std::vector<long long> heap;

void ShiftUp() {
  int i = size - 1;
  while (i > 0) {
    int j = (i - 1) / 2;
    if (heap[i] > heap[j]) {
      std::swap(heap[i], heap[j]);
      i = j;
    } else {
      break;
    }
  }
}

void ShiftDown() {
  int i = 0;
  while (i < size) {
    int child1 = (2 * i + 1 < size ? 2 * i + 1 : i);
    int child2 = (2 * i + 2 < size ? 2 * i + 2 : i);
    if (heap[i] < std::max(heap[child1], heap[child2])) {
      if (heap[child1] >= heap[child2]) {
        std::swap(heap[i], heap[child1]);
        i = child1;
      } else {
        std::swap(heap[i], heap[child2]);
        i = child2;
      }
    } else {
      break;
    }
  }
}

void Insert(long long num, int k) {
  if (size < k) {
    heap.push_back(num);
    size++;
    ShiftUp();
  } else if (num < heap[0]) {
    std::swap(heap[0], heap[--size]);
    ShiftDown();
    heap.push_back(num);
    size++;
    ShiftUp();
  }
}

void Merge(int start, int mid, int end) {
  int i = start, j = mid + 1, k = 0;
  long long temp[1003] = {0};
  while (i <= mid && j <= end) {
    if (heap[i] <= heap[j]) {
      temp[k] = heap[i];
      i++;
    } else {
      temp[k] = heap[j];
      j++;
    }
    k++;
  }
  while (i <= mid) {
    temp[k] = heap[i];
    i++;
    k++;
  }
  while (j <= end) {
    temp[k] = heap[j];
    j++;
    k++;
  }
  for (int i = start; i <= end; i++) {
    heap[i] = temp[i - start];
  }
}

void MergeSort(int start, int end) {
  if (start == end) {
    return;
  }
  int mid = (start + end) / 2;
  MergeSort(start, mid);
  MergeSort(mid + 1, end);
  Merge(start, mid, end);
}

int main() {
  int n, k;
  std::cin >> n >> k;
  long long a0, x, y;
  std::cin >> a0 >> x >> y;
  for (int i = 0; i < n; i++) {
    long long a = (x * a0 % 1073741824 + y % 1073741824) % 1073741824;
    Insert(a, k);
    a0 = a;
  }
  MergeSort(0, size - 1);
  for (int i = 0; i < size; i++) {
    std::cout << heap[i] << " ";
  }
}

/*
void HeapifyMax(std::vector<long long>& arr, long long i) {
  int size = arr.size();
  long long largest = i;
  if (2 * i + 1 < size && arr[2 * i + 1] > arr[largest]) {
    largest = 2 * i + 1;
  }
  if (2 * i + 2 < size && arr[2 * i + 2] > arr[largest]) {
    largest = 2 * i + 2;
  }
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    HeapifyMax(arr, largest);
  }
}

void Insert(std::vector<long long>& arr, long long num) {
  int size = arr.size();
  if (size == 0) {
    arr.push_back(num);
  } else {
    if (num < arr[0]) {
      int i, size = arr.size();
      for (i = 0; i < size; i++) {
        if (arr[0] == arr[i]) {
          break;
        }
      }
      std::swap(arr[i], arr[size - 1]);
      arr.pop_back();
    }
    arr.push_back(num);
    for (int i = size / 2 - 1; i >= 0; i--) {
      HeapifyMax(arr, i);
    }
  }
}

int main() {
  long long size, k, a, x, y;
  std::cin >> size >> k;
  std::vector<long long> arr;
  std::cin >> a >> x >> y;
  int num = x * a + y;
  arr.push_back(num);
  for (int i = 1; i <= size; i++) {
    long long num = ((x * arr[i - 1]) % 1073741824 + y % 1073741824) % 1073741824;
    Insert(arr, num);
  }
  for (int i = 1; i <= k; i++) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}


void Merge(int* arr, int l, int r) {
  int mid = l + (r - l) / 2;
  int i = 0, j = 0;
  int* res = new int[r - l];
  while (l + i < mid && mid + j < r) {
    if (arr[l + i] < arr[mid + j]) {
      res[i + j] = arr[l + i];
      i++;
    } else {
      res[i + j] = arr[mid + j];
      j++;
    }
  }
  while (l + i < mid) {
    res[i + j] = arr[l + i];
    i++;
  }
  while (mid + j < r) {
    res[i + j] = arr[mid + j];
    j++;
  }
  for (int z = 0; z < r - l; z++) {
    arr[l + z] = res[z];
  }
  delete[] res;
}

void MergeSort(int* arr, int start, int end) {
  if (start + 1 < end) {
    return;
  }
  int mid = start + (end - start) / 2;
  MergeSort(arr, start, mid);
  MergeSort(arr, mid + 1, end);
  Merge(arr, start, end);
}
 * * * ** * * * *  * * * * * * * * * * * *
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