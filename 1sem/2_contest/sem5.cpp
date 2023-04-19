#include <iostream>
#include <cstring> 

void Find(int* arr, int target, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; i <= size; j++) {
      if (arr[i] + arr[j] == target) {
        std::cout << '[' << i << ',' << j << ']' << std::endl;
      } else {
        continue;
      }
    }   
  }
}

int main() {
  char str[10000];
  int target, i = 0, j = 0;
  std::cin >> str >> target;
  int* arr = new int[strlen(str)];
  for(i = 0; i < strlen(str); i++) {
    if(str[i] == '[' || str[i] == ']' || str[i] == ',') {
      continue;
    } else {
      arr[j] = str[i];
      j++;
    }
  }
  Find(arr, target, j);
  delete[] arr;
  return 0;
}