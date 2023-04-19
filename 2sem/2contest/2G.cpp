#include <iostream>
#include <vector>

std::vector<std::vector<bool> > TransitiveMatrix(
    int size, std::vector<std::vector<bool> > matrix) {
  for (int k = 0; k < size; ++k) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
      }
    }
  }
  return matrix;
}

void PrintMatrix(int size, std::vector<std::vector<bool> > trans_matrix) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << trans_matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  int size;
  std::cin >> size;
  std::vector<std::vector<bool> > matrix;
  for (int i = 0; i < size; ++i) {
    std::vector<bool> tmp;
    for (int j = 0; j < size; ++j) {
      int num;
      std::cin >> num;
      tmp.push_back(num != 0);
    }
    matrix.push_back(tmp);
  }
  std::vector<std::vector<bool> > trans_matrix = TransitiveMatrix(size, matrix);
  PrintMatrix(size, trans_matrix);
  return 0;
}
