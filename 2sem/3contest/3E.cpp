#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

class Solution {
 private:
  struct Node {
    int64_t value = 0;
    std::vector<std::pair<int64_t, int64_t>> neighbours;
    bool used = false;
    void addNeighbours(const std::pair<int64_t, int64_t>& vert_and_weight) {
      neighbours.push_back(vert_and_weight);
    }
  };
  struct Graph {
    std::vector<Node> adj_list;

    Graph(const int64_t& num_of_vertexes) : adj_list(num_of_vertexes + 1) {
      for (int64_t i = 0; i <= num_of_vertexes; ++i) {
        adj_list[i].value = i;
        adj_list[i].used = false;
      }
    }
    void AddEdge(const Edge& edge) {
      adj_list[edge.from].addNeighbours({edge.to, edge.weight});
      adj_list[edge.to].addNeighbours({edge.from, edge.weight});
    }
    void MakeAllFalse() {
      for (auto& i : adj_list) {
        i.used = false;
      }
    }
  };

  struct DSU {
    int64_t Get(const int64_t& vertex) {
      int64_t node = vertex;
      for (; node != body_[node]; node = body_[node]);
      return body_[vertex] = node;
    }

    int64_t GetTotalWeight() const { return total_val_; }

    void Union(const Edge& unit, Graph& graph) {
      std::pair<int64_t, int64_t> two = {Get(unit.from),
                                         Get(unit.to)};
      int64_t root = 0;
      if (two.first == two.second) {
        return;
      }
      graph.AddEdge(unit);
      root = (body_[(rang_[two.first] > rang_[two.second]) ? two.second : two.first] =
               (rang_[two.first] > rang_[two.second]) ? two.first : two.second);
      total_val_ += unit.weight;
      rang_[root] += static_cast<int64_t>(rang_[two.first] == rang_[two.second]);
    }

    DSU(const int64_t& num_of_vertexes) {
      body_.resize(num_of_vertexes + 1, 0);
      rang_.resize(num_of_vertexes + 1);
    }

   private:
    std::vector<int64_t> body_;
    std::vector<int64_t> rang_;
    int64_t total_val_ = 0;
  };

  void ToSort(std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& left, const Edge& right) {
      if (left.weight == right.weight) {
        return left.from < right.from;
      } else {
        return left.weight < right.weight;
      }
    });
  }

  Graph graph_;
  DSU dsu_;
  const int64_t kBigNum = SIZE_MAX;

  void DFS(std::pair<Node*, Node*> node_pair, int64_t& res) {
    graph_.adj_list[node_pair.first->value].used = true;
    if (node_pair.first->value == node_pair.second->value) {
      return;
    }
    int64_t res1 = 0;
    for (auto& i : graph_.adj_list[node_pair.first->value].neighbours) {
      if (graph_.adj_list[i.first].used) {
        continue;
      }
      DFS({&graph_.adj_list[i.first], node_pair.second},
          res1 = std::min(res, static_cast<int64_t>(i.second)));
      if (res1 != 0) {
        res = res1;
        return;
      }
    }
    res = 0;
  }

 public:
  Solution(const int64_t& num_of_vertexes, std::vector<Edge>& edges)
      : graph_(num_of_vertexes), dsu_(num_of_vertexes) {
    ToSort(edges);
    for (const auto& i : edges) {
      dsu_.Union(i, graph_);
    }
  }

  int64_t GetAnswer(const std::pair<int64_t, int64_t>& vertex_pair) {
    graph_.MakeAllFalse();
    int64_t res = kBigNum;
    DFS({&graph_.adj_list[vertex_pair.first],&graph_.adj_list[vertex_pair.second]}, res);
    return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cout.tie(0);

  int64_t num_of_vertexes, num_of_edges, num_of_calls;
  std::cin >> num_of_vertexes >> num_of_edges >> num_of_calls;

  std::vector<Edge> edges(num_of_edges);

  while (num_of_edges-- > 0) {
    std::cin >> edges[edges.size() - num_of_edges - 1].from >>
                edges[edges.size() - num_of_edges - 1].to >>
                edges[edges.size() - num_of_edges - 1].weight;
  }

  Solution solution(num_of_vertexes, edges);

  std::pair<int64_t, int64_t> vertex_pair;
  while (num_of_calls-- > 0) {
    std::cin >> vertex_pair.first >> vertex_pair.second;
    std::cout << solution.GetAnswer(vertex_pair) << '\n';
  }

  return 0;
}