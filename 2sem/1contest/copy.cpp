#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<int> answer;
  std::vector<std::vector<int> > connections;
  std::vector<bool> black;

 public:
  Graph(int planets);
  ~Graph();
  bool Exists(int vec, int index);
  void AddConnection(int up, int down);
  void Cycle();
  bool DFS(int start, int end);
};

Graph::Graph(int planets) {
  answer = std::vector<int> ();
  connections.resize(planets);
  black.resize(planets);
}

Graph::~Graph() {}

bool Graph::Exists(int vec, int index) {
  for (size_t i = 0; i < connections[vec].size(); ++i) {
    if (connections[vec].at(i) == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddConnection(int up, int down) {
  int index_up = up - 1;
  if (!Exists(index_up, down)) {
    connections[index_up].push_back(down);
  }
}

void Graph::Cycle() {
  bool result = false;
  size_t length = black.size();
  for (size_t i = 0; i < length; ++i) {
    int value = i + 1;
    if (DFS(value, value)) {
      result = true;
      break;
    }
  }
  if (result) {
    std::cout << "YES" << std::endl;
    size_t index = 0;
    while (index < answer.size() - 1) {
      std::cout << answer[index] << " ";
      ++index;
    }
    std::cout << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}

bool Graph::DFS(int start, int end) {
  std::vector<int> stack;
  stack.push_back(start);
  while (!stack.empty()) {
    int i = start - 1;
    if (black[i]) {
      answer.clear();
      return false;
    }
    stack.pop_back();
    black[i] = true;
    answer.push_back(start);
    for (size_t j = 0; j < connections[i].size(); ++j) {
      if (connections[i].at(j) == end) {
        answer.push_back(end);
        return true;
      } else {
        int index = connections[i].at(j) - 1;
        if (!black[index]) {
          start = connections[i].at(j);
          stack.push_back(start);
        }
      }
    }
  }
  return false;
}

int main() {
  int points = 4;
  int roads = 4;
  Graph gr(points);
  gr.AddConnection(1, 2);
  gr.AddConnection(2, 3);
  gr.AddConnection(3, 4);
  gr.AddConnection(4, 2);
  gr.Cycle();
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
    int pointA, pointB;
    std::cin >> pointA >> pointB;
    graph.AddConnection(pointA, pointB);
    --roads;
  }
  graph.Cycle();
  return 0;
*/