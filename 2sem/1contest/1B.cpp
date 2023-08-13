#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Graph {
 private:
  struct Edge {
    size_t dist;
    size_t weight;

    Edge(size_t dist_point, size_t weight_of_edge) : dist(dist_point), weight(weight_of_edge) {}
  };

  std::vector<std::vector<Edge>> adj_list;
  size_t total_planet_num;

 public:
  Graph(size_t planet_num);
  ~Graph();
  bool Exists(size_t planet_a, size_t planet_b);
  void AddEdge(size_t planet_a, size_t planet_b, size_t weight);
  void BFS(size_t start, size_t finish);
};

Graph::Graph(size_t planet_num) : total_planet_num(planet_num) {
  adj_list.resize(planet_num);
}

Graph::~Graph() {}

bool Graph::Exists(size_t planet_a, size_t planet_b) {
  for (auto i : adj_list[planet_a]) {
    if (i.dist == planet_b)
      return true;
  }
  return false;
}

void Graph::AddEdge(size_t planet_a, size_t planet_b, size_t weight) {
  if (!Exists(planet_a, planet_b)) {
    adj_list[planet_a].emplace_back(planet_b, weight);
  }
}

void Graph::BFS(size_t start, size_t finish) {
  const size_t INF = std::numeric_limits<size_t>::max();
  std::vector<size_t> distance(total_planet_num, INF);
  distance[start] = 0;

  std::queue<size_t> q;
  q.push(start);

  while (!q.empty()) {
    size_t current = q.front();
    q.pop();

    for (const auto& edge : adj_list[current]) {
      size_t neighbor = edge.dist;
      size_t weight = edge.weight;

      if (distance[neighbor] > distance[current] + weight) {
        distance[neighbor] = distance[current] + weight;
        q.push(neighbor);
      }
    }
  }

  if (distance[finish] == INF) {
    std::cout << -1 << '\n';
  } else {
    std::cout << distance[finish] << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  size_t planet_num, jump_num;
  std::cin >> planet_num >> jump_num;
  Graph graph(planet_num);
  size_t start, finish;
  std::cin >> start >> finish;
  while (jump_num != 0) {
    size_t planet_a, planet_b, weight;
    std::cin >> planet_a >> planet_b >> weight;
    graph.AddEdge(planet_a - 1, planet_b - 1, weight);
    --jump_num;
  }
  if (start == finish) {
    std::cout << 0 << '\n';
  } else {
    graph.BFS(start - 1, finish - 1);
  }
  return 0;
}
