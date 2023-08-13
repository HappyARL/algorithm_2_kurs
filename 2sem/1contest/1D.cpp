#include <iostream>
#include <vector>


class DSU {
 private:
  std::vector<size_t> ancestors_;
  std::vector<std::vector<size_t> > answer_;
  std::vector<size_t> ranks_;

  size_t FindSet(size_t elem) {
    if (elem == ancestors_[elem]) {
      return elem ;
    }
    return ancestors_[elem] = FindSet(ancestors_[elem]);
  }

 public:
  DSU(size_t vertices);
  ~DSU();
  bool AreSame(size_t vertex_a, size_t vertex_b);
  void Unite(size_t vertex_a, size_t vertex_b);
  void Print();
};

DSU::DSU(size_t vertices) {
  ancestors_ = std::vector<size_t>(vertices, 0);
  answer_.resize(vertices);
  for (size_t i = 0; i < vertices; ++i) {
    ancestors_[i] = i;
  }
  ranks_ = std::vector<size_t>(vertices, 0);
}

DSU::~DSU() {}

bool DSU::AreSame(size_t vertex_a, size_t vertex_b) {
  return FindSet(vertex_a) == FindSet(vertex_b);
}

void DSU::Unite(size_t vertex_a, size_t vertex_b) {
  vertex_a = FindSet(vertex_a);
  vertex_b = FindSet(vertex_b);
  if (vertex_a != vertex_b) {
    if (ranks_[vertex_a] < ranks_[vertex_b]) {
      std::swap(vertex_a, vertex_b);
    }
    ancestors_ [vertex_b] = vertex_a;
    if (ranks_[vertex_b] == ranks_[vertex_a]) {
      ++ranks_[vertex_a];
    }
  }
}

void DSU::Print() {
  for (size_t i = 0; i < ancestors_.size(); ++i) {
    answer_[FindSet(i)].push_back(i + 1);
  }

  size_t count = 0;
  for (size_t i = 0; i < answer_.size(); ++i) {
    if (answer_[i].size() != 0) {
      ++count;
    }
  }

  std::cout << count << '\n';

  for (size_t i = 0; i < answer_.size(); ++i) {
    if (answer_[i].size() != 0) {
      std::cout << answer_[i].size() << '\n';
      for (size_t j = 0; j < answer_[i].size(); ++j) {
        std::cout << answer_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
}

int main() {
  size_t robots, connections;
  std::cin >> robots >> connections;
  DSU dsu(robots);
  while (connections != 0) {
    size_t robot_a, robot_b;
    std::cin >> robot_a >> robot_b;
    dsu.Unite(--robot_a, --robot_b);
    --connections;
  }
  dsu.Print();
  return 0;
}