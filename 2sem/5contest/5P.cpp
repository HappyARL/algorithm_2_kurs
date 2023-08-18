#include <iostream>
#include <vector>

using namespace std;

int main() {
  string S;
  cin >> S;

  int n = S.length();
  vector<int> countPrefix(n, 0);

  int countOnes = 0;
  for (int i = 0; i < n; ++i) {
    if (S[i] == '1') {
      countOnes++;
    }
    countPrefix[i] = countOnes;
  }

  int totalTriplets = 0;
  for (int j = 1; j < n - 1; ++j) {
    if (S[j] == '1') {
      int leftOnes = countPrefix[j - 1];
      int rightOnes = countOnes - countPrefix[j];

      if (j - leftOnes == leftOnes && n - j - 1 == rightOnes) {
        totalTriplets++;
      }
    }
  }

  cout << totalTriplets << endl;

  return 0;
}
