#include <iostream>
#include <vector>

std::vector<int> FindAnswerX(int** dp, int* x, int i, int j) {
  std::vector<int> vec;
  while (i != 0) {
    if (dp[i][j] > dp[i - 1][j] && dp[i][j] > dp[i][j - 1]) {
      vec.push_back(x[i]);
      --i;
      --j;
    } else {
      if (dp[i][j] == dp[i - 1][j]) {
        --i;
      } else {
        --j;
      }
    }
  }
  return vec;
}

std::vector<int> FindAnswerY(int** dp, int* y, int i, int j) {
  std::vector<int> vec;
  while (i != 0) {
    if (dp[i][j] > dp[i - 1][j] && dp[i][j] > dp[i][j - 1]) {
      vec.push_back(y[j]);
      --i;
      --j;
    } else {
      if (dp[i][j] == dp[i - 1][j]) {
        --i;
      } else {
        --j;
      }
    }
  }
  return vec;
}

std::vector<int> LCS(int* x, int* y, int m, int n) {
  int** dp = new int*[m + 1];
  for (int i = 0; i < m + 1; ++i) {
    dp[i] = new int[n + 1];
  }
  for (int i = 0; i <= m; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i <= n; ++i) {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (x[i] == y[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  std::vector<int> vec;
  if (m < n) {
    vec = FindAnswerX(dp, x, m, n);
  } else {
    vec = FindAnswerY(dp, y, m, n);
  }
  for (int i = 0; i <= m; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return vec;
}

int main() {
  int m;
  std::cin >> m;
  int* arr1 = new int[m + 1];
  arr1[0] = 0;
  for (int i = 1; i <= m; ++i) {
    std::cin >> arr1[i];
  }
  int n;
  std::cin >> n;
  int* arr2 = new int[n + 1];
  arr2[0] = 0;
  for (int i = 1; i <= n; ++i) {
    std::cin >> arr2[i];
  }
  std::vector<int> ans = LCS(arr1, arr2, m, n);
  for (int i = (int)ans.size() - 1; i >= 0; --i) {
    std::cout << ans[i] << " ";
  }
  delete[] arr1;
  delete[] arr2;
  return 0;
}
