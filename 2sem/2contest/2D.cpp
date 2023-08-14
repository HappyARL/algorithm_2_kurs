#include <iostream>
#include <vector>

const int64_t kInf = 0xffffffff;

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

class Graph {
 private:
  std::vector<Edge> adj_list;
  std::vector<int64_t> dist;
  int64_t vertices;

 public:
  explicit Graph(int64_t vertices_num);
  ~Graph();
  void addEdge(int64_t from, int64_t to, int64_t weight);
  void searchCycle();
  void printCycle();
};

Graph::Graph(int64_t vertices_num) : vertices(vertices_num) {
  dist.resize(vertices + 1, kInf);
}

Graph::~Graph() = default;

void Graph::addEdge(int64_t from, int64_t to, int64_t weight) {
  adj_list.push_back({from, to, weight});
}

void Graph::searchCycle() {
  dist[1] = 0;
  int64_t num = vertices;

  while (num > 0) {
    for (const auto& iter : adj_list) {
      if (dist[iter.from] + iter.weight < dist[iter.to]) {
        dist[iter.to] = dist[iter.from] + iter.weight;
      } else {
        dist[iter.to] = dist[iter.to];
      }
    }
    --num;
  }

  printCycle();
}

void Graph::printCycle() {
  for (int64_t num = 1; num <= vertices; ++num) {
    int64_t distance = (dist[num] >= 30000) ? 30000 : dist[num];
    std::cout << distance << ' ';
  }
}

int main() {
  int64_t vertices_num, edges_num;
  std::cin >> vertices_num >> edges_num;

  Graph graph(vertices_num);

  while (edges_num != 0) {
    int64_t ver_from, ver_to, ver_weight;
    std::cin >> ver_from >> ver_to >> ver_weight;
    graph.addEdge(ver_from, ver_to, ver_weight);
    --edges_num;
  }

  graph.searchCycle();

  return 0;
}
