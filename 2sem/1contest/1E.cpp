#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<int> answer_;
  std::vector<std::vector<int> > connections_;
  std::vector<bool> visited_;
  bool cycle_;

 public:
  Graph(int value);
  ~Graph();
  bool Exists(int vec, int index);
  void AddConnection(int point_a, int point_b);
  void TopologicalSort();
  void DFS(int index, std::vector<bool> black);
  void Print();
};

Graph::Graph(int value) {
  answer_ = std::vector<int>();
  connections_.resize(value);
  visited_.resize(value);
  cycle_ = false;
}

Graph::~Graph() {}

bool Graph::Exists(int vec, int index) {
  for (size_t i = 0; i < connections_[vec].size(); ++i) {
    if (connections_[vec].at(i) == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddConnection(int point_a, int point_b) {
  int index_point_a = point_a - 1;
  if (!Exists(index_point_a, point_b)) {
    connections_[index_point_a].push_back(point_b);
  }
}

void Graph::TopologicalSort() {
  int size = (int)visited_.size();
  for (int i = 0; i < size; ++i) {
    std::vector<bool> black(size, false);
    if (!visited_[i]) {
      DFS(i, black);
    }
  }
}

void Graph::DFS(int index, std::vector<bool> black) {
  visited_[index] = true;
  black[index] = true;
  for (size_t j = 0; j < connections_[index].size(); ++j) {
    int i = connections_[index].at(j) - 1;
    if (black[i]) {
      cycle_ = true;
    }
    if (!visited_[i]) {
      DFS(i, black);
    }
  }
  answer_.push_back(index + 1);
}

void Graph::Print() {
  if (cycle_) {
    std::cout << "-1" << std::endl;
  } else {
    std::vector<int> sorted;
    while (!answer_.empty()) {
      sorted.push_back(answer_.back());
      answer_.pop_back();
    }
    int size = (int)sorted.size();
    for (int i = 0; i < size; ++i) {
      std::cout << sorted[i] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  int vertexs, edges;
  std::cin >> vertexs >> edges;
  Graph graph(vertexs);
  while (edges != 0) {
    int point_a, point_b;
    std::cin >> point_a >> point_b;
    graph.AddConnection(point_a, point_b);
    --edges;
  }
  graph.TopologicalSort();
  graph.Print();
  return 0;
}
