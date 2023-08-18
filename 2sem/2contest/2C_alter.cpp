#include <iostream>
#include <vector>
#include <algorithm>

const int64_t INF = 1e18;

struct Edge {
  int64_t from;
  int64_t to;
  int64_t cost;
  int64_t time;
};

class Graph {
 private:
  std::vector<Edge> adjList;
  std::vector<int64_t> distance;
  std::vector<int64_t> total_time;
  std::vector<int64_t> parents;
  int64_t vertices;
  int64_t max_time;

 public:
  Graph(int64_t vertex_num, int64_t edge_num, int64_t max_time);
  void addEdge(const Edge& edge);
  void BellmanFord();
  void printPath();
};

Graph::Graph(int64_t vertex_num, int64_t edge_num, int64_t max_time) : vertices(vertex_num), max_time(max_time) {
  adjList.reserve(edge_num);
  distance.assign(vertex_num, INF);
  total_time.resize(vertex_num, INF);
  parents.assign(vertex_num, -1);
}

void Graph::addEdge(const Edge& edge) {
  adjList.push_back(edge);
}

void Graph::BellmanFord() {
  distance[0] = 0;
  total_time[0] = 0;

  for (int i = 0; i < vertices - 1; ++i) {
    for (const Edge& edge : adjList) {
      if (distance[edge.from] < INF && distance[edge.from] + edge.cost < distance[edge.to]) {
        distance[edge.to] = distance[edge.from] + edge.cost;
        total_time[edge.to] = total_time[edge.from] + edge.time;
        parents[edge.to] = edge.from;
      }
    }
  }
}

void Graph::printPath() {
  int64_t finish = vertices - 1;

  if (total_time[finish] > max_time) {
    std::cout << "-1" << '\n';
    return;
  }

  std::vector<int64_t> path;
  for (int64_t cur = finish; cur != -1; cur = parents[cur]) {
    path.push_back(cur);
  }
  std::reverse(path.begin(), path.end());

  std::cout << distance[finish] << '\n';
  std::cout << path.size() << '\n';
  for (int64_t iter : path) {
    std::cout << iter + 1 << ' ';
  }
}

int main() {
  int64_t vertex_num, edge_num, max_time;
  std::cin >> vertex_num >> edge_num >> max_time;

  Graph graph(vertex_num, edge_num, max_time);

  while (edge_num--) {
    int64_t from, to, cost, time;
    std::cin >> from >> to >> cost >> time;
    graph.addEdge({from - 1, to - 1, cost, time});
  }

  graph.BellmanFord();

  graph.printPath();

  return 0;
}
