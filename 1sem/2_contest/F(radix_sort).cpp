#include <iostream>

void RadixSort(std::string* arr, int length) {
  int num_arr[64] = {0};
  for(int i = 0; i < 64; i++) {
    for(int j = 0; j < length; j++) {
      num_arr[i] = arr[i][j];
    }
  }
}

int main() {
  int length;
  std::cin >> length;
  std::string* arr = new std::string[length]; 
  for (int i = 0; i < length; i++) {
    long long int num;
    std::cin >> num;
    while (num != 0){
        arr[i] += (num % 2 == 0 ? "0" : "1" );
        num /= 2;
    }
  }
  RadixSort(arr, length);
  delete[] arr;
  return 0;
}

/*
void CountSort(long long int* arr, int n, long long int exp) {
  long long int* output = new long long int[n];
  int i, count[19] = {0};
  for (i = 0; i < n; i++) {
    count[(arr[i] / exp) % 10]++;
  }
  for (i = 1; i < 19; i++) {
    count[i] += count[i - 1];
  }
  for (i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }
  for (i = 0; i < n; i++) {
    arr[i] = output[i];
  }
  delete[] output;
}

void Radixsort(long long int* arr, int n) {
  long long int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  for (long long int exp = 1; max / exp > 0; exp *= 10) {
    CountSort(arr, n, exp);
  }
}

int main() {
  int length;
  std::cin >> length;
  long long int* arr = new long long int[length];
  for (int i = 0; i < length; i++) {
    std::cin >> arr[i];
  }
  Radixsort(arr, length);
  delete[] arr;
  return 0;

  ***********************
  // Online C++ compiler to run C++ program online
#include <iostream>

int main() {
  int length;
  std::cin >> length;
  std::string* arr = new std::string[length]; 
  for (int i = 0; i < length; i++) {
    long long int num;
    std::cin >> num;
    while (num != 0){
        arr[i] += (num % 2 == 0 ? "0" : "1" );
        num /= 2;
    }
    std::cout << i+1 << " num "<< arr[i] << std::endl;
  }
  int* num_arr = new int[length];
  for(int i = 0; i < 1; i++) {
    for(int j = 0; j < length; j++) {
      //num_arr[j] = arr[i][j] - 48;
      std::cout << arr[j][i] << " ";
    }
  }
  for(int i = 0; i < length; i++) {
    std::cout << num_arr[i] << " ";
  }
  delete[] arr;
  delete[] num_arr;
  return 0;
}
}*/
