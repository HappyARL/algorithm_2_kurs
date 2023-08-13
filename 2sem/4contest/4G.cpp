// original - вроде емакс

#include <iostream>
#include <queue>
#include <vector>

const int MAX_VERTICES = 1001;
const int64_t INF = 0x3f3f3f3f;

struct Edge {
  int64_t from;
  int64_t to;
  int64_t capacity;
  int64_t flow;
};

class FlowGraph {
 private:
  std::vector<Edge> edges;
  std::vector<int64_t> adj_list[MAX_VERTICES];
  int64_t distance[MAX_VERTICES];
  int64_t current_edge[MAX_VERTICES];
  bool visited[MAX_VERTICES];

  int64_t source;
  int64_t sink;

 public:
  FlowGraph(int64_t num_vertices);
  ~FlowGraph();
  void add_edge(int64_t from, int64_t to, int64_t capacity);
  void print();
  bool BFS();
  int64_t DFS(int64_t u, int64_t min_capacity);
  int64_t Dinic();
};

FlowGraph::FlowGraph(int64_t num_vertices) : source(1), sink(num_vertices) {}

FlowGraph::~FlowGraph() = default;

void FlowGraph::add_edge(int64_t from, int64_t to, int64_t capacity) {
  edges.push_back((Edge){from, to, capacity, 0});
  edges.push_back((Edge){to, from, 0, 0});
  adj_list[from].push_back((int64_t)edges.size() - 2);
  adj_list[to].push_back((int64_t)edges.size() - 1);
}

void FlowGraph::print() {
  int64_t max_flow = Dinic();

  std::cout << max_flow << std::endl;
  for (size_t i = 0; i < edges.size(); i += 2) {
    std::cout << edges[i].flow << std::endl;
  }
}

bool FlowGraph::BFS() {
  for (int64_t i = 0; i < MAX_VERTICES; i++) {
    visited[i] = false;
    distance[i] = 0;
  }
  std::queue<int64_t> q;
  q.push(source);
  distance[source] = 0;
  visited[source] = true;
  while (!q.empty()) {
    int64_t u = q.front();
    q.pop();
    for (int64_t i = 0; i < (int64_t)adj_list[u].size(); i++) {
      Edge& e = edges[adj_list[u][i]];
      if (!visited[e.to] && e.capacity > e.flow) {
        visited[e.to] = true;
        distance[e.to] = distance[u] + 1;
        q.push(e.to);
      }
    }
  }
  return visited[sink];
}

int64_t FlowGraph::DFS(int64_t u, int64_t min_capacity) {
  if (u == sink || min_capacity == 0) return min_capacity;
  int64_t flow = 0, f;
  for (int64_t& i = current_edge[u]; i < (int64_t)adj_list[u].size(); i++) {
    Edge& e = edges[adj_list[u][i]];
    if (distance[e.to] == distance[u] + 1 && (f = DFS(e.to, std::min(min_capacity, e.capacity - e.flow))) > 0) {
      flow += f;
      min_capacity -= f;
      e.flow += f;
      edges[adj_list[u][i] ^ 1].flow -= f;
      if (min_capacity == 0) break;
    }
  }
  return flow;
}

int64_t FlowGraph::Dinic() {
  int64_t max_flow = 0;
  while (BFS()) {
    for (int64_t i = 0; i < MAX_VERTICES; i++) {
      current_edge[i] = 0;
    }
    max_flow += DFS(source, INF);
  }
  return max_flow;
}

int main() {
  int64_t num_vertices, num_edges;
  std::cin >> num_vertices >> num_edges;

  FlowGraph flow_graph(num_vertices);

  while (num_edges != 0) {
    int64_t u, v, w;
    std::cin >> u >> v >> w;
    flow_graph.add_edge(u, v, w);
    --num_edges;
  }

  flow_graph.print();

  return 0;
}



//#include <iostream>
//#include <vector>
//#include <queue>
//
//const int kMax = 500;
//const int64_t kkInf = 1000000000;
//
//struct Edge {
//  int64_t src;
//  int64_t dst;
//  int64_t capacity;
//  int64_t flow;
//};
//
//class Graph {
// private:
//  std::vector<int> adj_list_[kMax];
//  int current_[kMax];
//  bool visited_[kMax];
//  int64_t level_[kMax];
//  int64_t end_;
//
// public:
//  std::vector<Edge> edges;
//  Graph(int64_t t);
//  ~Graph();
//  void AddEdge(int64_t vert_a, int64_t vert_b, int64_t weight);
//  bool BFS();
//  int64_t DFS(int64_t position, int64_t min_flow);
//  int64_t FindMaxFlow();
//};
//
//Graph::Graph(int64_t t) : end_(t) {}
//
//Graph::~Graph() {}
//
//void Graph::AddEdge(int64_t vert_a, int64_t vert_b, int64_t weight) {
//  Edge one{vert_a, vert_b, weight, 0};
//  edges.push_back(one);
//  Edge two{vert_a, vert_b, 0, 0};
//  edges.push_back(two);
//  int64_t m = edges.size();
//  adj_list_[vert_a].push_back(m - 2);
//  adj_list_[vert_b].push_back(m - 1);
//}
//
//bool Graph::BFS() {
//  for (int i = 0; i < kMax; ++i) {
//    visited_[i] = false;
//  }
//  std::queue<int> queue;
//  queue.push(1);
//  level_[1] = 0;
//  visited_[1] = true;
//  while (!queue.empty()) {
//    int vert_u = queue.front();
//    queue.pop();
//    for (size_t j = 0; j < adj_list_[vert_u].size(); ++j) {
//      int i = adj_list_[vert_u][j];
//      Edge& edge = edges[i];
//      if (!visited_[edge.dst] && edge.capacity > edge.flow) {
//        visited_[edge.dst] = true;
//        level_[edge.dst] = level_[vert_u] + 1;
//        queue.push(edge.dst);
//      }
//    }
//  }
//  return visited_[end_];
//}
//
//int64_t Graph::DFS(int64_t position, int64_t min_flow) {
//  if (position == end_ || min_flow == 0) {
//    return min_flow;
//  }
//  int64_t flow = 0;
//  int64_t delta;
//  for (size_t j = 0; j < adj_list_[position].size(); ++j) {
//    int i = adj_list_[position][j];
//    Edge& edge = edges[i];
//    if (level_[edge.dst] == level_[position] + 1 && (delta = DFS(edge.dst, std::min(min_flow, edge.capacity - edge.flow))) > 0) {
//      flow += delta;
//      min_flow -= delta;
//      edge.flow += delta;
//      edges[i ^ 1].flow -= delta;
//      if (min_flow == 0) {
//        break;
//      }
//    }
//  }
//  return flow;
//}
//
//int64_t Graph::FindMaxFlow() {
//  int64_t max_flow = 0;
//  while (BFS()) {
//    for (int i = 0; i < kMax; ++i) {
//      current_[i] = 0;
//    }
//    while (int64_t flow = DFS(1, kkInf)) {
//      max_flow += flow;
//    }
//  }
//  return max_flow;
//}
//
//int main() {
//  std::ios::sync_with_stdio(0);
//  std::cin.tie(0);
//  int64_t vert_num, edge_num;
//  std::cin >> vert_num >> edge_num;
//  Graph graph(vert_num);
//  for (int64_t i = 0; i < edge_num; i++) {
//    int64_t vert_a, vert_b, weight;
//    std::cin >> vert_a >> vert_b >> weight;
//    graph.AddEdge(vert_a, vert_b, weight);
//  }
//  int64_t max_flow = graph.FindMaxFlow();
//  std::cout << max_flow << '\n';
//  for (size_t i = 0; i < graph.edges.size(); ++i) {
//    if (i % 2 == 0) {
//      std::cout << graph.edges[i].flow << '\n';
//    }
//  }
//  return 0;
//}
//
