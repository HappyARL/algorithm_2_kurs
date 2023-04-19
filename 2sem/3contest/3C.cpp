#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct Vertex {
  T root;
  T strength;
};

template <typename T>
struct Edge {
  T src_vertex;
  Vertex<T> dst_vertex;
};

template <typename T>
class DSU {
 private:
  std::vector<Vertex<T> > verteces;

 public:
  DSU(T students);
  ~DSU();
  void Unite(T student_a, T student_b, T power);
  Vertex<T> Find(T student_a);
  T FriendshipPower(T student_a);
  bool Ask(T vertex_a, T vertex_b);
};

template <typename T>
DSU<T>::DSU(T students) {
  Vertex<T> point;
  verteces.resize(students);
  for (int i = 0; i < students; ++i) {
    point.root = i;
    point.strength = 0;
    verteces[i] = point;
  }
}

template <typename T>
DSU<T>::~DSU() {}

template <typename T>
void DSU<T>::Unite(T student_a, T student_b, T power) {
  T root_a = Find(student_a).root;
  T root_b = Find(student_b).root;
  if (root_a != root_b) {
    verteces[root_b].root = root_a;
    T total_power = verteces[root_b].strength + power;
    verteces[root_a].strength += total_power;
  } else {
    verteces[root_a].strength += power;
  }
}

template <typename T>
Vertex<T> DSU<T>::Find(T student_a) {
  if (verteces[student_a].root != student_a) {
    verteces[student_a] = Find(verteces[student_a].root);
  }
  return verteces[student_a];
}

template <typename T>
bool DSU<T>::Ask(T vertex_a, T vertex_b) {
  if (Find(vertex_a).root == Find(vertex_b).root) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
class Graph {
 private:
 public:
  std::vector<std::vector<Vertex<T> > > connections;
  Graph(T verteces);
  ~Graph();
  bool Exists(T vertex, T index);
  void AddConnection(T vertex_a, T vertex_b, T weight);
};

template <typename T>
Graph<T>::Graph(T verteces) {
  connections.resize(verteces);
}

template <typename T>
Graph<T>::~Graph() {}

template <typename T>
bool Graph<T>::Exists(T vertex, T index) {
  for (size_t i = 0; i < connections[vertex].size(); ++i) {
    if (connections[vertex].at(i).root == index) {
      return true;
    }
  }
  return false;
}

template <typename T>
void Graph<T>::AddConnection(T vertex_a, T vertex_b, T weight) {
  T index_a = vertex_a - 1;
  T index_b = vertex_b - 1;
  if (!Exists(index_a, index_b)) {
    Vertex<T> tmp;
    tmp.root = index_b;
    tmp.strength = weight;
    connections[index_a].push_back(tmp);
    tmp.root = index_a;
    tmp.strength = weight;
    connections[index_b].push_back(tmp);
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
  int count = (int)graph.connections.size();
  std::priority_queue<Vertex<T>, std::vector<Vertex<T> >, CompareVertex<T> > pqueue;
  std::vector<bool> visited(count, false);
  T sum = 0;
  Vertex<T> first_vertex;
  first_vertex.root = 0;
  first_vertex.strength = 0;
  pqueue.push(first_vertex);
  while (!pqueue.empty()) {
    T u = pqueue.top().root;
    T u_weight = pqueue.top().strength;
    pqueue.pop();
    if (!visited[u]){
      visited[u] = true;
      sum += u_weight;
      for (auto x : graph.connections[u]) {
        T v = x.root;
        T weight = x.strength;
        if (!visited[v]) {
          Vertex<T> tmp;
          tmp.root = v;
          tmp.strength = weight;
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
  int count = (T)graph.connections.size();
  std::priority_queue<Edge<T>, std::vector<Edge<T> >, CompareEdges<T> > pqueue;
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < (int)graph.connections.at(i).size(); ++j) {
      Edge<T> edge;
      edge.src_vertex = i;
      edge.dst_vertex.root = graph.connections[i][j].root;
      edge.dst_vertex.strength = graph.connections[i][j].strength;
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
  int64_t verteces;
  int64_t edges;
  std::cin >> verteces >> edges;
  Graph<int64_t> graph(verteces);
  while (edges != 0) {
    int64_t vertex_a, vertex_b, weight;
    std::cin >> vertex_a >> vertex_b >> weight;
    graph.AddConnection(vertex_a, vertex_b, weight);
    --edges;
  }
  std::cout << MST_PRIM(graph) << std::endl;
  std::cout << MST_KRUSKAL(graph) << std::endl;
  return 0;
}

/*
int main() {
  int verteces = 4;
  int edges = 4;
  Graph<int> graph(verteces);
  graph.AddConnection(1, 2, 1);
  graph.AddConnection(2, 3, 2);
  graph.AddConnection(3, 4, 5);
  graph.AddConnection(4, 1, 4);
  std::cout << MST_PRIM(graph) << std::endl;
  std::cout << MST_KRUSKAL(graph) << std::endl;
  return 0;
}
*/