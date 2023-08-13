#include <iostream>
#include <vector>
#include <algorithm>

const int64_t INF = 100000;

struct Edge {
  int64_t from, to, weight;

  Edge(int64_t ver_from, int64_t ver_to, int64_t ver_weight) : from(ver_from),
                                                               to(ver_to),
                                                               weight(ver_weight) {}
};

class Graph {
 private:
  std::vector<Edge> adj_matrix_;
  std::vector<int64_t> cycle;
  int64_t vertices_num;
  
 public:
  Graph(int64_t vertices);
  ~Graph();
  void addEdge(int64_t from, int64_t to, int64_t weight);
  void printCycle();
  bool hasNegativeCycle(int64_t n);
  
};

Graph::Graph(int64_t vertices) : vertices_num(vertices) {}

Graph::~Graph() = default;

void Graph::addEdge(int64_t from, int64_t to, int64_t weight) {
  adj_matrix_.emplace_back(from, to, weight);
}

void Graph::printCycle() {
  if (hasNegativeCycle(vertices_num)) {
    std::cout << "YES" << '\n';

    std::cout << cycle.size() << '\n';
    for (int64_t vertex : cycle) {
      std::cout << vertex + 1 << " ";
    }
    std::cout << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
}

bool Graph::hasNegativeCycle(int64_t n) {
  std::vector<int64_t> dist(n, INF);
  dist[0] = 0;

  for (int64_t i = 0; i < n - 1; ++i) {
    for (const Edge& edge : adj_matrix_) {
      if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
        cycle.push_back(edge.to);
        dist[edge.to] = dist[edge.from] + edge.weight;
      }
    }
  }

  cycle.push_back(cycle.front());

  for (const Edge& edge : adj_matrix_) {
    if (dist[edge.from] != INF && dist[edge.from] + edge.weight < dist[edge.to]) {
      return true;
    }
  }

  return false;
}

int main() {
  int64_t vertices;
  std::cin >> vertices;

  Graph graph(vertices);

  if (vertices == 1) {
    std::cout << "NO" << '\n';
    return 0;
  }

  for (int64_t i = 0; i < vertices; ++i) {
    for (int64_t j = 0; j < vertices; ++j) {
      int64_t weight;
      std::cin >> weight;
      if (weight != INF) {
        graph.addEdge(i, j, weight);
      }
    }
  }

  graph.printCycle();

  return 0;
}
