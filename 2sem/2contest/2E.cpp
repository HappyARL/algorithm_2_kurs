#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

class Graph {
 private:
  std::vector<Edge> adjList;
  std::vector<int64_t> curr_distance;
  std::vector<int64_t> dist_from_source;
  int64_t vertex_num;

 public:
  Graph(int64_t vertices) : vertex_num(vertices) {
    curr_distance.resize(vertices);
    dist_from_source.resize(vertices, -1);
  }

  void addEdge(const Edge& edge) {
    adjList.push_back(edge);
  }

  void BellmanFord() {
    int64_t num = 0;
    for (int64_t i = 0; i < vertex_num; ++i) {
      num = -1;
      for (auto & j : adjList) {
        if (dist_from_source[j.to] <= dist_from_source[j.from] + j.weight) continue;
        dist_from_source[j.to] = std::max(int64_t(-1000000), dist_from_source[j.from] + j.weight);
        curr_distance[j.to] = j.from;
        num = j.to;
      }
    }

    if (num == -1) {
      std::cout << "NO" << '\n';
      return;
    }

    for (int64_t i = 0; i < vertex_num; ++i) {
      num = curr_distance[num];
    }

    std::vector<int64_t> cycle;
    for (int64_t t = num;; t = curr_distance[t]) {
      cycle.push_back(t);
      if (cycle.size() > 1 && t == num) {
        break;
      }
    }

    std::cout << "YES" << '\n';
    std::cout << cycle.size() << '\n';
    for (int64_t i = int64_t(cycle.size()) - 1; i >= 0; --i) {
      std::cout << cycle[i] + 1 << ' ';
    }
  }
};

int main() {
  int64_t vertex_num;
  std::cin >> vertex_num;

  Graph graph(vertex_num);

  for (int64_t i = 0; i < vertex_num; i++) {
    for (int64_t j = 0; j < vertex_num; j++) {
      int64_t cost = 0;
      std::cin >> cost;
      if (cost != 100000) {
        graph.addEdge({i, j, cost});
      }
    }
  }

  graph.BellmanFord();

  return 0;
}
