#include <iostream>
#include <vector>
#include <queue>

struct Vertex {
  int64_t root;
  int64_t strength;

  Vertex() = default;
  Vertex(int64_t ver_root, int64_t ver_strength) : root(ver_root), strength(ver_strength) {}
};

struct Edge {
  int64_t src_vertex;
  Vertex dst_vertex;

  Edge(int64_t src, Vertex vert) : src_vertex(src), dst_vertex(vert) {}
};

class DSU {
 private:
  std::vector<Vertex> vertices;

 public:
  explicit DSU(int64_t students);
  ~DSU();
  void Unite(int64_t student_a, int64_t student_b, int64_t power);
  Vertex Find(int64_t student_a);
  bool Ask(int64_t vertex_a, int64_t vertex_b);
};

DSU::DSU(int64_t students) {
  vertices.resize(students);
  for (int i = 0; i < students; ++i) {
    vertices[i] = {i, 0};
  }
}

DSU::~DSU() = default;

void DSU::Unite(int64_t student_a, int64_t student_b, int64_t power) {
  Vertex root_a = Find(student_a);
  Vertex root_b = Find(student_b);
  if (root_a.root != root_b.root) {
    vertices[root_b.root].root = root_a.root;
    vertices[root_a.root].strength += vertices[root_b.root].strength + power;
  } else {
    vertices[root_a.root].strength += power;
  }
}

Vertex DSU::Find(int64_t student_a) {
  if (vertices[student_a].root != student_a) {
    vertices[student_a] = Find(vertices[student_a].root);
  }
  return vertices[student_a];
}

bool DSU::Ask(int64_t vertex_a, int64_t vertex_b) {
  if (Find(vertex_a).root == Find(vertex_b).root) {
    return true;
  }
  return false;
}

class Graph {
 private:
 public:
  std::vector<std::vector<Vertex > > adj_list;
  Graph(int64_t vertices);
  ~Graph();
  bool exists(int64_t vertex, int64_t index);
  void addEdge(int64_t vertex_a, int64_t vertex_b, int64_t weight);
};

Graph::Graph(int64_t vertices) {
  adj_list.resize(vertices);
}

Graph::~Graph() = default;

bool Graph::exists(int64_t vertex, int64_t index) {
  for (const auto& iter : adj_list[vertex]) {
    if (iter.root == index) return true;
  }
  return false;
}

void Graph::addEdge(int64_t vertex_a, int64_t vertex_b, int64_t weight) {
  if (!exists(vertex_a, vertex_b)) {
    adj_list[vertex_a].emplace_back(vertex_b, weight);
    adj_list[vertex_b].emplace_back(vertex_a, weight);
  }
}

class CompareEdges {
 public:
  bool operator()(Edge edge_a, Edge edge_b) {
    return edge_a.dst_vertex.strength > edge_b.dst_vertex.strength;
  }
};

int64_t MST_KRUSKAL(Graph graph) {
  size_t count = graph.adj_list.size();

  std::priority_queue<Edge, std::vector<Edge>, CompareEdges> pqueue;

  for (size_t i = 0; i < count; ++i) {
    for (size_t j = 0; j < graph.adj_list[i].size(); ++j) {
      Edge edge((int64_t)i, {graph.adj_list[i][j].root, graph.adj_list[i][j].strength});
      pqueue.push(edge);
    }
  }

  DSU dsu((int64_t)count);
  int64_t sum = 0;

  while (!pqueue.empty()) {
    int64_t u = pqueue.top().src_vertex;
    int64_t v = pqueue.top().dst_vertex.root;
    int64_t weight = pqueue.top().dst_vertex.strength;
    pqueue.pop();
    if (!dsu.Ask(u, v)) {
      sum += weight;
      dsu.Unite(u, v, weight);
    }
  }

  return sum;
}

int main() {
  int64_t vertices;
  int64_t edges;
  std::cin >> vertices >> edges;

  Graph graph(vertices);

  while (edges != 0) {
    int64_t vertex_a, vertex_b, weight;
    std::cin >> vertex_a >> vertex_b >> weight;
    graph.addEdge(vertex_a - 1, vertex_b - 1, weight);
    --edges;
  }

  std::cout << MST_KRUSKAL(graph) << '\n';
  return 0;
}
