#include <iostream>
#include <vector>
#include <queue>

struct Vertex {
  int root;
  int strength;
};

class Graph {
 private:
 public:
  std::vector<std::vector<Vertex> > connections;
  std::vector<int> salary;
  Graph(int verteces);
  ~Graph();
  bool Exists(int vertex, int index);
  void AddConnection(int vertex_a, int vertex_b, int weight);
};

Graph::Graph(int verteces) {
  for (int i = 0; i < verteces; ++i) {
    std::vector<Vertex> tmp;
    tmp.resize(verteces);
    connections.push_back(tmp);
  }
  salary.resize(verteces);
}

Graph::~Graph() {}

bool Graph::Exists(int vertex, int index) {
  for (size_t i = 0; i < connections[vertex].size(); ++i) {
    if (connections[vertex].at(i).root == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddConnection(int vertex_a, int vertex_b, int weight) {
  int index_a = vertex_a - 1;
  int index_b = vertex_b - 1;
  if (!Exists(index_a, index_b)) {
    Vertex tmp;
    tmp.root = index_b;
    tmp.strength = weight;
    connections[index_a].push_back(tmp);
    tmp.root = index_a;
    tmp.strength = weight;
    connections[index_b].push_back(tmp);
  }
}

class CompareVertex {
 public:
  bool operator()(Vertex pair_a, Vertex pair_b) {
    return pair_a.strength > pair_b.strength;
  }
};

int MST_PRIM(Graph graph) {
  int count = (int)graph.connections.size();
  std::priority_queue<Vertex, std::vector<Vertex>, CompareVertex> pqueue;
  std::vector<bool> visited(count, false);
  int sum = 0;
  Vertex first_vertex;
  first_vertex.root = 0;
  first_vertex.strength = 0;
  pqueue.push(first_vertex);
  while (!pqueue.empty()) {
    int u = pqueue.top().root;
    int u_weight = pqueue.top().strength;
    pqueue.pop();
    if (!visited[u]){
      visited[u] = true;
      sum += u_weight;
      for (auto x : graph.connections[u]) {
        int v = x.root;
        int weight = x.strength;
        if (!visited[v]) {
          Vertex tmp;
          tmp.root = v;
          tmp.strength = weight;
          pqueue.push(tmp);
        }
      }
    }
  }
  return sum;
}

int main() {
  int verteces;
  std::cin >> verteces;
  Graph graph(verteces);
  for (int i = 0; i < verteces; ++i) {
    for (int j = 0; j < verteces; ++j) {
      Vertex tmp;
      int num;
      std::cin >> num;
      tmp.root = j;
      tmp.strength = num;
      graph.connections[i][j] = tmp;
    }
  }
  while (verteces != 0) {
    int payment;
    std::cin >> payment;
    graph.salary.push_back(payment);
    --verteces;
  }
  std::cout << MST_PRIM(graph) << std::endl;
  return 0;
}
