#include <iostream>
#include <vector>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t count;

  bool operator<(const Edge& other) const {
    return count < other.count;
  }
};

class Graph {
 private:
  std::vector<Edge> adjList;
  std::vector<bool> used;
  std::vector<int64_t> tin;
  std::vector<int64_t> tup;
  std::vector<Edge> answer;
  int64_t vertices;
  int64_t timer;

 public:
  Graph(int64_t vertex_num);
  ~Graph();
  void addEdge(const Edge& edge);
  void DFS(const Edge& edge, int64_t pos = -1);
  void findBridges();
  void printBridges();
};

Graph::Graph(int64_t vertex_num) : vertices(vertex_num) {
  used.resize(vertices, false);
  tin.resize(vertices, -1);
  tup.resize(vertices, -1);
}

Graph::~Graph() = default;

void Graph::addEdge(const Edge &edge) {
  adjList.push_back(edge);
}

void Graph::DFS(const Edge& edge, int64_t pos) {
  used[edge.from] = true;
  tin[edge.from] = tup[edge.from] = timer++;
  for (const auto& iter : adjList) {
    if (iter.from == pos) continue; // Fix 1
    if (used[iter.to]) {
      tup[edge.from] = std::min(tup[edge.from], tin[iter.to]);
    } else {
      DFS(iter, iter.from); // Fix 2
      tup[edge.from] = std::min(tup[edge.from], tup[iter.to]);
      if (tup[iter.to] > tin[iter.from]) { // Fix 3
        answer.push_back(edge);
      }
    }
  }
}

void Graph::findBridges() {
  timer = 0;
  for (int64_t i = 0; i < vertices; ++i) {
    if (!used[i]) {
      DFS(i);
    }
  }
  printBridges();
}

void Graph::printBridges() {
  std::sort(answer.begin(), answer.end());

  std::cout << answer.size() << '\n';
  for (const auto& iter : answer) {
    std::cout << iter.count << " ";
  }
  std::cout << '\n';
}

int main() {
  int64_t vertex_num, edge_num;
  std::cin >> vertex_num >> edge_num;

  Graph graph(vertex_num);
  int count = 1;

  while (edge_num != 0) {
    int64_t from, to;
    std::cin >> from >> to;
    graph.addEdge({from - 1, to - 1, count});
    ++count;
    --edge_num;
  }

  graph.findBridges();

  return 0;
}