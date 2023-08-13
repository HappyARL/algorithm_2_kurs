#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> adj_list_;
  std::vector<bool> visited_;
  std::vector<bool> recursion_stack_;
  std::vector<int> result_;

 public:
  Graph(int vertices);
  ~Graph();
  bool Exists(int vec, int index);
  void AddEdge(int up, int down);
  bool Cycle();
  bool DFS(int index);
  void Print();
};

Graph::Graph(int vertices) {
  adj_list_.resize(vertices);
  visited_.resize(vertices, false);
  recursion_stack_.resize(vertices, false);
}

Graph::~Graph() {}

bool Graph::Exists(int vec, int index) {
  for (const auto& iter : adj_list_[vec]) {
    if (iter == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddEdge(int up, int down) {
  if (!Exists(up, down)) {
    adj_list_[up].push_back(down);
  }
}

bool Graph::Cycle() {
  for (size_t v = 0; v < adj_list_.size(); ++v) {
    if (!visited_[v] && DFS(v)) {
      return true;
    }
  }
  return false;
}

bool Graph::DFS(int index) {
  if (recursion_stack_[index]) {
    return true;
  }

  if (!visited_[index]) {
    visited_[index] = true;
    recursion_stack_[index] = true;
    result_.push_back(index);

    for (int u : adj_list_[index]) {
      if (DFS(u)) {
        return true;
      }
    }
  }
  recursion_stack_[index] = false;
  return false;
}

void Graph::Print() {
  if (Cycle()) {
    std::cout << "YES" << '\n';
    for (size_t i = 0; i < result_.size(); ++i) {
      std::cout << result_[i] + 1 << " ";
    }
  } else {
    std::cout << "NO" << '\n';
  }
}

int main() {
  int vertices, edges;
  std::cin >> vertices >> edges;
  Graph gr(vertices);

  while (edges != 0) {
    int point_a, point_b;
    std::cin >> point_a >> point_b;
    gr.AddEdge(point_a - 1, point_b - 1);
    --edges;
  }

  gr.Print();

  return 0;
}
