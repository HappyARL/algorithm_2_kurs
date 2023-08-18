#include <cmath>
#include <iostream>
#include <vector>

class Tree {
 private:
  std::vector<std::vector<int64_t> > edges_;
  std::vector<std::vector<int64_t> > sparse_table_;
  std::vector<int64_t> ETT_;
  std::vector<int64_t> Height_;
  std::vector<int64_t> tin_;
  std::vector<bool> visited_;
  int64_t time_;

 public:
  Tree(int64_t vertices);
  ~Tree();
  bool Exists(int64_t vertex_a, int64_t vertex_b);
  void AddEdge(int64_t vertex_a, int64_t vertex_b);
  void SparseTable();
  int64_t RMQ(int64_t left, int64_t right);
  void DFS(int64_t index, int64_t height);
  int64_t LCA(int64_t vertex_a, int64_t vertex_b);
};

Tree::Tree(int64_t vertices) : time_(0) {
  edges_.resize(vertices);
  tin_.resize(vertices);
  visited_.resize(vertices);
  int64_t length = 2 * vertices - 1;
  for (int64_t i = 0; i < length; ++i) {
    std::vector<int64_t> tmp;
    tmp.resize(length + 1);
    sparse_table_.push_back(tmp);
  }
}

Tree::~Tree() {}

bool Tree::Exists(int64_t vertex_a, int64_t vertex_b) {
  for (const auto& i : edges_[vertex_a]) {
    if (i == vertex_b) {
      return true;
    }
  }
  return false;
}

void Tree::AddEdge(int64_t vertex_a, int64_t vertex_b) {
  if (!Exists(vertex_a, vertex_b)) {
    edges_[vertex_a].push_back(vertex_b);
    edges_[vertex_b].push_back(vertex_a);
  }
}

void Tree::SparseTable() {
  auto length = (int64_t)Height_.size();
  for (int i = 0; i < log2(length) + 1; i++) {
    sparse_table_[i][0] = Height_[i];
  }
  for (int i = 1; i <= log2(length) + 1; i++) {
    for (int j = 0; (j + (1 << i)) <= length; j++) {
      sparse_table_[i][j] = std::min(sparse_table_[i - 1][j],
                                     sparse_table_[i - 1][j + (1 << (i - 1))]);
    }
  }
}

int64_t Tree::RMQ(int64_t left, int64_t right) {
  if (left == right) {
    return left;
  }
  auto index = (int64_t)log2(right - left + 1);
  return std::min(sparse_table_[index][left],
                  sparse_table_[index][right - (1 << index) + 1]);
}

void Tree::DFS(int64_t index, int64_t height) {
  tin_[index] = time_++;
  visited_[index] = true;
  ETT_.push_back(index);
  Height_.push_back(height);
  for (size_t j = 0; j < edges_[index].size(); ++j) {
    int i = edges_[index].at(j);
    if (!visited_[i]) {
      height++;
      DFS(i, height);
      //ETT_.push_back(index);
      //Height_.push_back(height);
    }
  }
}

int64_t Tree::LCA(int64_t vertex_a, int64_t vertex_b) {
  int64_t left = tin_[vertex_a];
  int64_t right = tin_[vertex_b];
  if (left == right) {
    return 0;
  }
  if (left > right) {
    std::swap(left, right);
  }
  int64_t parent_height = Height_[ETT_[RMQ(left, right)]];
  return (Height_[vertex_a] - parent_height) + (Height_[vertex_b] - parent_height);
}

int main() {
  int64_t vertices;
  std::cin >> vertices;
  Tree tree(vertices);
  --vertices;
  while (vertices != 0) {
    int64_t vertex_a, vertex_b;
    std::cin >> vertex_a >> vertex_b;
    tree.AddEdge(vertex_a - 1, vertex_b - 1);
    --vertices;
  }
  int64_t requests;
  std::cin >> requests;
  tree.DFS(0, 1);
  tree.SparseTable();
  while (requests != 0) {
    int64_t vertex_a, vertex_b;
    std::cin >> vertex_a >> vertex_b;
    std::cout << tree.LCA(vertex_a - 1, vertex_b - 1) << std::endl;
    --requests;
  }
  return 0;
}
