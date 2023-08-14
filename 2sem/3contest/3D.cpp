#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

class DSU {
 private:
  std::vector<int64_t> body_;
  std::vector<int64_t> rang_;
  int64_t total_val_ = 0;
  
 public:
  DSU(int64_t num_of_vertexes) {
    body_.resize(num_of_vertexes + 1);
    rang_.resize(num_of_vertexes + 1);
    std::iota(body_.begin(), body_.end(), 0);
  }
  
  int64_t Find(int64_t vertex) {
    int64_t node = vertex;
    while (node != body_[node]) {
      node = body_[node];
    }
    return body_[vertex] = node;
  }

  void Union(const Edge& unit) {
    std::pair<int64_t, int64_t> two = {Find(unit.from),Find(unit.to)};
    int64_t root = 0;
    if (two.first == two.second) {
      return;
    }
    if (rang_[two.first] > rang_[two.second]) {
      root = body_[two.second] = two.first;
    } else {
      root = body_[two.first] = two.second;
    }
    total_val_ += unit.weight;
    rang_[root] += static_cast<int64_t>(rang_[two.first] == rang_[two.second]);
  }

  int64_t FindTotal() const { return total_val_; }
};

class Graph {
 private:
  DSU dsu_;
  void SortEdges(std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& left, const Edge& right) {
      if (left.weight == right.weight) {
        return left.from < right.from;
      } else {
        return left.weight < right.weight;
      }
    });
  }

 public:
  Graph(int64_t num_of_vertexes, std::vector<Edge>& edges);
  ~Graph();
  int64_t sumCost() const;
};

Graph::Graph(int64_t num_of_vertexes, std::vector<Edge> &edges)  : dsu_(num_of_vertexes) {
  SortEdges(edges);
  for (const auto& i : edges) {
    dsu_.Union(i);
  }
}

Graph::~Graph() = default;

int64_t Graph::sumCost() const {
  return dsu_.FindTotal();
}

int main() {
  int64_t num_of_vertexes;
  std::cin >> num_of_vertexes;

  std::vector<Edge> edges;
  edges.reserve(num_of_vertexes * num_of_vertexes);

  for (int64_t i = 1; i <= num_of_vertexes; ++i) {
    for (int64_t j = 1; j <= num_of_vertexes; ++j) {
      int64_t weight;
      std::cin >> weight;
      edges.push_back({i, j, weight});
    }
  }

  for (int64_t i = 1; i <= num_of_vertexes; ++i) {
    int64_t weight;
    std::cin >> weight;
    edges.push_back({i, num_of_vertexes + 1, weight});
  }

  Graph graph(num_of_vertexes + 1, edges);

  std::cout << graph.sumCost();

  return 0;
}