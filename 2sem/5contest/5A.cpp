#include <iostream>
#include <vector>

std::vector<int64_t> PrefixFunction(const std::string& main_string) {
  std::vector<int64_t> pi_vec;
  pi_vec.assign(main_string.length(), 0);
  for (size_t i = 1; i < main_string.length(); ++i) {
    int64_t j = pi_vec[i - 1];
    // пока символ на позиции j не равен символу на позиции i уменьшаем суффикс
    while (j > 0 && main_string[i] != main_string[j]) {
      j = pi_vec[j - 1];
    }
    (main_string[i] == main_string[j]) ? pi_vec[i] = j + 1 : pi_vec[i] = j;
  }
  return pi_vec;
}

void Knuth_Morris_Pratt(const std::string& source, const std::string& pattern) {
  std::vector<int64_t> pi_vec = PrefixFunction(pattern + '#' + source);
  for (size_t i = 0; i < source.length(); ++i) {
    if (pi_vec[pattern.length() + 1 + i] == pattern.length()) {
      std::cout << i - pattern.length() + 1 << '\n';
    }
  }
}

int main() {
  std::string source;
  std::string pattern;
  std::cin >> source;
  std::cin >> pattern;
  Knuth_Morris_Pratt(source, pattern);
  return 0;
}
