#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  std::cout << std::fixed;
  std::cout << std::setprecision(10);
  int length, check;
  std::cin >> length;
  double arr[300000] = {};
  for (int i = 0; i < length; i++) {
    double num;
    std::cin >> num;
    arr[i + 1] = log(num) + arr[i];
  }
  std::cin >> check;
  while (check != 0) {
    int start, end;
    std::cin >> start >> end;
    std::cout << std::exp((arr[end + 1] - arr[start]) / (end - start + 1))
              << std::endl;
    check--;
  }
  return 0;
}
/*1
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
  int num, test;
  std::cin >> num;
  double arr[100000];
  double prefix[100000];
  for(int i = 0; i < num; i++) {
    std::cin >> arr[i];
    if(i == 0) {
      prefix[i] = arr[i];  
    } else {
      prefix[i] = prefix[i - 1] * arr[i];
    }
  }  
  std::cin >> test;
  while(test != 0) {
    int start, end;
    std::cin >> start >> end;
    std::cout << std::fixed << std::setprecision(10) << pow((prefix[end]/ prefix[start]) * arr[start], (double)1 / (end - start + 1)) << std::endl;
  }
  return 0;
}

with log:

#include <iostream>
#include <iomanip>
#include <cmath>

void sound(double* arr, int l, int r) {
  double sum = 0;
  for (int i = l; i <= r; i++) {
    sum += log(arr[i]);
  }
  std::cout << std::fixed << std::setprecision(10) << exp(sum / (r - l + 1)) << std::endl;
}
int main() {
  int num, test;
  std::cin >> num;
  double arr[100000];
  for(int i = 0; i < num; i++) {
    std::cin >> arr[i];
  }
  std::cin >> test;
  while(test != 0) {
    int start, end;
    std::cin >> start >> end;
    sound(arr, start, end);
    test--;
  }
  return 0;
}



-------------------------------------------------

double fillPrefixSum(double* arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        arr[i] = arr[i - 1] * arr[i];
    }
    return pow(arr[r], (double)1 / (r - l + 1));
}

int main()
{
    double arr[] = { 79.02, 36.68, 79.83, 76.00, 95.48, 48.84, 49.95, 91.91 };
    int start = 2, end = 7;
    std::cout << std::fixed << std::setprecision(10) << fillPrefixSum(arr, start, end) << std::endl;
}
*/