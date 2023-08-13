#include <iostream>
#include <vector>
#include <limits>  // Include limits for INT_MAX

class Graph {
 private:
  std::vector<std::vector<int64_t> > adj_matrix;
  int64_t amount;

 public:
  std::vector<int64_t> salary;
  Graph(int64_t vertices);
  ~Graph();
  bool Exists(int64_t vertex_a, int64_t vertex_b);
  void AddConnection(int64_t vertex_a, int64_t vertex_b, int64_t weight);
  int64_t minKey(std::vector<int64_t> key, std::vector<bool> mstSet);
  int64_t MST_PRIM();
};

Graph::Graph(int64_t vertices) : amount(vertices) {
  for (int64_t i = 0; i < vertices; ++i) {
    std::vector<int64_t> tmp(vertices, 0);
    adj_matrix.push_back(tmp);
  }
  salary.resize(vertices);
}

Graph::~Graph() {}

bool Graph::Exists(int64_t vertex_a, int64_t vertex_b) {
  // Fix the condition for checking if an edge exists
  if (adj_matrix[vertex_a][vertex_b] != 0 || adj_matrix[vertex_b][vertex_a] != 0) {
    return true;
  }
  return false;
}

void Graph::AddConnection(int64_t vertex_a, int64_t vertex_b, int64_t weight) {
  // Fix the condition for adding an edge
  if (!Exists(vertex_a, vertex_b)) {
    adj_matrix[vertex_a][vertex_b] = adj_matrix[vertex_b][vertex_a] = weight;
  }
}

int64_t Graph::minKey(std::vector<int64_t> key, std::vector<bool> mstSet) {
  int64_t min = std::numeric_limits<int64_t>::max();  // Use the correct constant
  int64_t min_index = -1;

  for (int64_t v = 0; v < amount; ++v) {
    if (!mstSet[v] && key[v] < min) {
      min = key[v];
      min_index = v;
    }
  }

  return min_index;
}

int64_t Graph::MST_PRIM() {
  std::vector<int64_t> parent(amount);
  std::vector<int64_t> key(amount, std::numeric_limits<int64_t>::max());  // Initialize with the correct constant
  std::vector<bool> mstSet(amount, false);

  key[0] = 0;
  parent[0] = -1;

  int64_t sum = 0;

  for (int count = 0; count < amount - 1; count++) {
    int u = minKey(key, mstSet);
    mstSet[u] = true;

    for (int v = 0; v < amount; ++v) {
      if (adj_matrix[u][v] && !mstSet[v] && adj_matrix[u][v] < key[v]) {
        sum += adj_matrix[u][v];
        parent[v] = u;
        key[v] = adj_matrix[u][v];
      }
    }
  }

  return sum;
}

int main() {
  int64_t amount;
  std::cin >> amount;

  Graph graph(amount);

  for (int i = 0; i < amount; ++i) {
    for (int j = 0; j < amount; ++j) {
      int64_t weight;
      std::cin >> weight;
      graph.AddConnection(i, j, weight);
    }
  }

  while (amount != 0) {
    int64_t money;
    std::cin >> money;
    graph.salary.push_back(money);
    --amount;
  }

  int64_t total_cost = graph.MST_PRIM();
//  for (int64_t s : graph.salary) {
//    total_cost += s;
//  }

  std::cout << total_cost << '\n';
  return 0;
}
