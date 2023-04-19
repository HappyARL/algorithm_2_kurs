#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
private:
  std::vector<std::vector<int>> neighbors_;
  std::vector<bool> visited_;
  std::vector<int> result_;
  bool cycle_;

public:
  Graph(int points);
  ~Graph();
  void AddConnection(int up, int down);
  void Cycle();
  void DFS(int start, std::vector<bool>& black);
};

Graph::Graph(int points) {
  neighbors_.resize(points);
  visited_.resize(points);
  cycle_ = false;
}

Graph::~Graph() {}

void Graph::AddConnection(int up, int down) {
  int index_up = up - 1;
  int index_down = down - 1;
  if (std::find(neighbors_[index_up].begin(), neighbors_[index_up].end(), index_down) == neighbors_[index_up].end()) {
    neighbors_[index_up].push_back(index_down);
  }
}

void Graph::Cycle() {
  int size = (int)visited_.size();
  for (int i = 0; i < size; ++i) {
    std::vector<bool> black(size);
    if (!cycle_) {
      if (!visited_[i]) {
        DFS(i, black);
      }
    }
  }
  if (cycle_) {
    std::cout << "YES" << std::endl;
    int size = (int)result_.size();
    bool check = false;
    for (int i = 0; i < size - 1; ++i) {
      if (result_[i] == result_.back()) {
        check = true;
      }
      if (check) {
        std::cout << result_[i] + 1 << " ";
      }
    }
    std::cout << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}

void Graph::DFS(int index, std::vector<bool>& black) {
  visited_[index] = true;
  black[index] = true;
  for (int neighbor : neighbors_[index]) {
    if (!cycle_) {
      if (black[neighbor]) {
        result_.push_back(index);
        result_.push_back(neighbor);
        cycle_ = true;
      } else if (!visited_[neighbor]) {
        result_.push_back(index);
        DFS(neighbor, black);
      }
    }
  }
}

int main() {
  int points, roads;
  std::cin >> points >> roads;
  Graph graph(points);
  while (roads != 0) {
    int point_a, point_b;
    std::cin >> point_a >> point_b;
    graph.AddConnection(point_a, point_b);
    --roads;
  }
  graph.Cycle();
  return 0;
}

/*

  int points = 2;
  int roads = 2;
  Graph gr(points);
  gr.AddConnection(1, 2);
  gr.AddConnection(1, 2);
  gr.Cycle();
  return 0;

int points, roads;
  std::cin >> points >> roads;
  Graph graph(points);
  while (roads != 0) {
    int point_a, point_b;
    std::cin >> point_a >> point_b;
    graph.AddConnection(point_a, point_b);
    --roads;
  }
  graph.Cycle();
  return 0;
*/