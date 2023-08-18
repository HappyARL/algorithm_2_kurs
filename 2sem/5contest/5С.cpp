#include <iostream>
#include <vector>

std::vector<int64_t> PrefixFunction(const std::string& main_string) {
  std::vector<int64_t> pi_vec;
  pi_vec.assign(main_string.length(), 0);

  for (size_t i = 1; i < main_string.length(); ++i) {
    int64_t j = pi_vec[i - 1];
    while (j > 0 && main_string[i] != main_string[j]) {
      j = pi_vec[j - 1];
    }
    (main_string[i] == main_string[j]) ? pi_vec[i] = j + 1 : pi_vec[i] = j;
  }

  return pi_vec;
}

bool Knuth_Morris_Pratt(const std::string& source, const std::string& pattern) {
  std::vector<int64_t> pi_vec = PrefixFunction(pattern + '#' + source);

  for (size_t i = 0; i < source.length(); ++i) {
    if (pi_vec[pattern.length() + 1 + i] == (int64_t)pattern.length()) {
      return true;
    }
  }

  return false;
}

int main() {
  std::string source;
  std::string pattern;

  std::cin >> pattern;
  std::cin >> source;
  int64_t count = 0;

  for (size_t shift = 0; shift < pattern.length(); ++shift) {
    std::string shifted_pattern = pattern.substr(shift) + pattern.substr(0, shift);
    if (Knuth_Morris_Pratt(source, shifted_pattern)) ++count;
  }

  std::cout << count << '\n';

  return 0;
}
