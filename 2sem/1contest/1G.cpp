// original - https://e-maxx.ru/algo/bridge_searching

#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t order;

  Edge(int64_t ver_from, int64_t ver_to, int64_t count = -1) : from(ver_from), to(ver_to), order(count) {}
  bool operator==(const Edge& other) const {
    if (this->from == other.from && this->to == other.to) {
      return true;
    }
    return false;
  }
};

class Graph {
 private:
  std::vector<std::vector<int64_t> > adj_list;
  std::vector<bool> used;
  std::vector<int64_t> tin;
  std::vector<int64_t> tup;
  std::vector<Edge> edge_list;
  std::vector<int64_t> answer;
  int64_t vertices_num;
  int64_t timer;

 public:
  Graph(int64_t vertices);
  ~Graph();
  void addEdge(int64_t ver_a, int64_t ver_b, int64_t count);
  void DFS(int64_t index, int64_t p = -1);
  void findBridges();
  void printBridge();
};

Graph::Graph(int64_t vertices) : vertices_num(vertices) {
  adj_list.resize(vertices);
  used.resize(vertices, false);
  tin.resize(vertices);
  tup.resize(vertices);
}

Graph::~Graph() = default;

void Graph::addEdge(int64_t ver_a, int64_t ver_b, int64_t count) {
  adj_list[ver_a].push_back(ver_b);
  adj_list[ver_b].push_back(ver_a);
  edge_list.emplace_back(Edge(ver_a, ver_b, count));
}

void Graph::DFS(int64_t index, int64_t p) {
  used[index] = true;
  tin[index] = tup[index] = timer++;
  for (size_t i = 0; i < adj_list[index].size(); ++i) {
    int64_t to = adj_list[index][i];
    if (to == p) {
      continue;
    }
    if (used[to])
      tup[index] = std::min(tup[index], tin[to]);
    else {
      DFS (to, index);
      tup[index] = std::min(tup[index], tup[to]);
      if (tup[to] > tin[index]) {
        Edge bridge(index, to);
        for (const auto& iter : edge_list) {
          if (iter == bridge) {
            answer.push_back(iter.order);
          }
        }
      }
    }
  }
}

void Graph::findBridges() {
  timer = 0;
  for (int64_t i = 0; i < vertices_num; ++i) {
    used[i] = false;
  }
  for (int64_t i = 0; i < vertices_num; ++i) {
    if (!used[i]) {
      DFS(i);
    }
  }
  printBridge();
}

void Graph::printBridge() {
  std::sort(answer.begin(), answer.end());

  std::cout << answer.size() << '\n';
  for (const auto& iter : answer) {
    std::cout << iter + 1 << " ";
  }
  std::cout << '\n';
}

int main() {
  int64_t vertices, edges;
  std::cin >> vertices >> edges;
  int64_t count = 0;

  Graph graph(vertices);

  while (edges != 0) {
    int64_t vertex_a, vertex_b;
    std::cin >> vertex_a >> vertex_b;
    graph.addEdge(vertex_a - 1, vertex_b - 1, count);
    ++count;
    --edges;
  }

  graph.findBridges();

  return 0;
}
