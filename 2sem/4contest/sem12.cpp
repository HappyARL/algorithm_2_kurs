//
// Created by Арлан on 20.04.2023.
//
#include <iostream>
#include <variant>

int main() {
  std::variant<int, double, std::string> v;
  v = "abc";
  //std::cout << std::get<int>(v) << '\n'; bad_variant_access
  std::cout << std::get<std::string>(v) << '\n';
  v = 5.f;
  std::cout << (std::holds_alternative<double>(v) ? "true" : "false") << '\n';
}
