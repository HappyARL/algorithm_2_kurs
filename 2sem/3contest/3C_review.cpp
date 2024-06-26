//
// Created by Арлан on 17.08.2023.
//

#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct Vertex {
  T root;
  T strength;

  Vertex() = default;
  Vertex(T ver_root, T ver_strength) : root(ver_root), strength(ver_strength) {}
};

template <typename T>
struct Edge {
  T src_vertex;
  Vertex<T> dst_vertex;

  Edge(T src, Vertex<T> vert) : src_vertex(src), dst_vertex(vert) {}
};

template <typename T>
class DSU {
 private:
  std::vector<Vertex<T> > vertices;

 public:
  explicit DSU(T students);
  ~DSU();
  void Unite(T student_a, T student_b, T power);
  Vertex<T> Find(T student_a);
  bool Ask(T vertex_a, T vertex_b);
};

template <typename T>
DSU<T>::DSU(T students) {
  Vertex<T> point;
  vertices.resize(students);
  for (int i = 0; i < students; ++i) {
    point.root = i;
    point.strength = 0;
    vertices[i] = point;
  }
}

template <typename T>
DSU<T>::~DSU() = default;

template <typename T>
void DSU<T>::Unite(T student_a, T student_b, T power) {
  Vertex<T> root_a = Find(student_a);
  Vertex<T> root_b = Find(student_b);
  if (root_a.root != root_b.root) {
    vertices[root_b.root].root = root_a.root;
    vertices[root_a.root].strength += vertices[root_b.root].strength + power;
  } else {
    vertices[root_a.root].strength += power;
  }
}


template <typename T>
Vertex<T> DSU<T>::Find(T student_a) {
  if (vertices[student_a].root != student_a) {
    vertices[student_a] = Find(vertices[student_a].root);
  }
  return vertices[student_a];
}

template <typename T>
bool DSU<T>::Ask(T vertex_a, T vertex_b) {
  if (Find(vertex_a).root == Find(vertex_b).root) {
    return true;
  }
  return false;
}

template <typename T>
class Graph {
 private:
 public:
  std::vector<std::vector<Vertex<T> > > adj_list;
  Graph(T vertices);
  ~Graph();
  bool Exists(T vertex, T index);
  void AddConnection(T vertex_a, T vertex_b, T weight);
};

template <typename T>
Graph<T>::Graph(T vertices) {
  adj_list.resize(vertices);
}

template <typename T>
Graph<T>::~Graph() {}

template <typename T>
bool Graph<T>::Exists(T vertex, T index) {
  for (const auto& iter : adj_list[vertex]) {
    if (iter.root == index) {
      return true;
    }
  }
  return false;
}

template <typename T>
void Graph<T>::AddConnection(T vertex_a, T vertex_b, T weight) {
  if (!Exists(vertex_a, vertex_b)) {
    adj_list[vertex_a].push_back({vertex_b, weight});
    adj_list[vertex_b].push_back({vertex_a, weight});
  }
}

template <typename T>
class CompareVertex {
 public:
  bool operator()(Vertex<T> pair_a, Vertex<T> pair_b) {
    return pair_a.strength > pair_b.strength;
  }
};

template <typename T>
T MST_PRIM(Graph<T> graph) {
  int count = static_cast<int>(graph.adj_list.size());
  std::priority_queue<Vertex<T>, std::vector<Vertex<T> >, CompareVertex<T> > pqueue;
  std::vector<bool> visited(count, false);
  T sum = 0;
  Vertex<T> first_vertex(0, 0);
  pqueue.push(first_vertex);
  while (!pqueue.empty()) {
    T u = pqueue.top().root;
    T u_weight = pqueue.top().strength;
    pqueue.pop();
    if (!visited[u]){
      visited[u] = true;
      sum += u_weight;
      for (auto x : graph.adj_list[u]) {
        T v = x.root;
        T weight = x.strength;
        if (!visited[v]) {
          Vertex<T> tmp(v, weight);
          pqueue.push(tmp);
        }
      }
    }
  }
  return sum;
}

template <typename T>
class CompareEdges {
 public:
  bool operator()(Edge<T> edge_a, Edge<T> edge_b) {
    return edge_a.dst_vertex.strength > edge_b.dst_vertex.strength;
  }
};

template <typename T>
T MST_KRUSKAL(Graph<T> graph) {
  size_t count = graph.adj_list.size();

  std::priority_queue<Edge<T>, std::vector<Edge<T> >, CompareEdges<T> > pqueue;

  for (size_t i = 0; i < count; ++i) {
    for (size_t j = 0; j < graph.adj_list[i].size(); ++j) {
      Edge<T> edge(i, {graph.adj_list[i][j].root, graph.adj_list[i][j].strength});
      pqueue.push(edge);
    }
  }

  DSU<T> dsu(count);
  T sum = 0;

  while (!pqueue.empty()) {
    T u = pqueue.top().src_vertex;
    T v = pqueue.top().dst_vertex.root;
    T weight = pqueue.top().dst_vertex.strength;
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
  Graph<int64_t> graph(vertices);
  while (edges != 0) {
    int64_t vertex_a, vertex_b, weight;
    std::cin >> vertex_a >> vertex_b >> weight;
    graph.AddConnection(vertex_a - 1, vertex_b - 1, weight);
    --edges;
  }
  //std::cout << MST_PRIM(graph) << '\n';
  std::cout << MST_KRUSKAL(graph) << '\n';
  return 0;
}

/*
int main() {
  int vertices = 4;
  int edges = 4;
  Graph<int> graph(vertices);
  graph.AddConnection(1, 2, 1);
  graph.AddConnection(2, 3, 2);
  graph.AddConnection(3, 4, 5);
  graph.AddConnection(4, 1, 4);
  std::cout << MST_PRIM(graph) << '\n';
  std::cout << MST_KRUSKAL(graph) << '\n';
  return 0;
}
*/