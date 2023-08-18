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
  edges.push_back({from, to, capacity, 0});
  edges.push_back({to, from, 0, 0});
  adj_list[from].push_back((int64_t)edges.size() - 2);
  adj_list[to].push_back((int64_t)edges.size() - 1);
}

void FlowGraph::print() {
  int64_t max_flow = Dinic();

  std::cout << max_flow << std::endl;
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
