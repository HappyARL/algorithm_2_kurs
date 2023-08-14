#include <cstdint>
#include <iostream>
#include <vector>

const int64_t kMax = 100000;

struct Edge {
  uint16_t from;
  uint16_t to;
  int weight;
};

struct Node {
  uint16_t value = 0;
  uint16_t parent = (uint16_t)-1;
  int dist = 0;
  std::vector<std::pair<uint16_t, int> > neighbours;
};

class Graph {
 private:
  std::vector<Node> adj_list_;
  std::vector<int64_t> dists_;
  int64_t vertices_num;

 public:
  Graph(int64_t vertices);
  ~Graph();
  void addEdge(int64_t from, int64_t to, int64_t weight);
  void searchNegCycle();
};

Graph::Graph(int64_t vertices) : vertices_num(vertices) {
  adj_list_.resize(vertices + 1);
  for (int64_t i = 1; i <= vertices; ++i) {
    adj_list_[i].value = i;
  }
  dists_.resize(vertices + 1, 0);
}

Graph::~Graph() = default;

void Graph::addEdge(int64_t from, int64_t to, int64_t weight) {
  adj_list_[from].neighbours.emplace_back(to, weight);
}

void Graph::searchNegCycle() {
  uint16_t loop_status = 0;
  std::vector<uint16_t> loop;
  uint16_t tmp = 0;
  std::pair<uint16_t, uint16_t> num = {vertices_num, vertices_num};
  while (num.first-- > 0) {
    tmp = uint16_t(-1);
    for (int64_t j = 1; j <= vertices_num; ++j) {
      for (const auto& k : adj_list_[j].neighbours) {
        if (dists_[k.first] > dists_[j] + k.second) {
          dists_[k.first] = dists_[j] + k.second;
          adj_list_[k.first].parent = j;
          tmp = k.first;
        }
      }
    }
    
    if (num.first != 0) {
      continue;
    }
    
    if (tmp == uint16_t(-1)) {
      std::cout << "NO";
      return;
    }
    
    std::cout << "YES\n";
    
    while (num.second-- > 0) {
      tmp = adj_list_[tmp].parent;
    }
    
    loop_status = tmp;
    
    while (true) {
      loop.push_back(loop_status);
      if (loop_status == tmp && loop.size() > 1) break;
      loop_status = adj_list_[loop_status].parent;
    }
    
    std::cout << loop.size() << '\n';
    for (int64_t j = (int64_t)loop.size() - 1; j >= 0; --j) {
      std::cout << loop[j] << ' ';
    }
  }
}

int main() {
  int64_t vertices_num;
  std::cin >> vertices_num;

  Graph graph(vertices_num);

  for (int64_t i = 0; i < vertices_num; ++i) {
    for (int64_t j = 0; j < vertices_num; ++j) {
      int64_t edge;
      std::cin >> edge;
      if (edge < 0 && i == j) {
        std::cout << "YES" << '\n';
        std::cout << i + 1 << ' ' << i + 1;
        return 0;
      }
      if (edge == kMax || i == j) continue;
      graph.addEdge(i + 1, j + 1, edge);
    }
  }

  graph.searchNegCycle();

  return 0;
}