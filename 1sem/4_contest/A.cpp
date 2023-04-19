#include <iostream>
#include <vector>

void Run(size_t r, size_t t, std::vector<int, int> run) {
  
}

void Cheer(size_t r, std::vector<int, int> run);

int main() {
  size_t n;
  std::cin >> n;
  std::vector<int, int> runners;
  while (n != 0) {
    std::string cmd;
    std::cin >> cmd;
    if (cmd == "RUN") {
      size_t runner, time;
      std::cin >> runner >> time;
      Run(runner, time, runners);
    }
    if (cmd == "CHEER") {
      size_t runner;
      std::cin >> runner;
      Cheer(runner, runners);
    }
    --n;
  }
  return 0;
}