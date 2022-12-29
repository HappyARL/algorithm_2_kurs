#include <iostream>
#include <vector>

const int kMod = 1e9;
long long Update(long long number, long long mod) {
  if (number < 0LL) {
    return (mod + number) % mod;
  }
  return number % mod;
}

int MaxPolindom(std::vector<int> arr, int n) {
  long long** dp = new long long*[n];
  for (int i = 0; i < n; ++i) {
    dp[i] = new long long[n];
  }
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }
  for (int i = 0; i < n - 1; ++i) {
    dp[i][i + 1] = 2 + static_cast<int>(arr[i] == arr[i + 1]);
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 2; j < n; ++j) {
      dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
      if (arr[i] == arr[j]) {
        dp[i][j] += dp[i + 1][j - 1] + 1;
      }
      dp[i][j] = Update(dp[i][j], kMod);
    }
  }
  int num = dp[0][n - 1];
  for (int i = 0; i < n; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return num;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cout << MaxPolindom(arr, n);
  return 0;
}
