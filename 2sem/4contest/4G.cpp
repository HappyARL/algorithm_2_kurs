#include <iostream>
#include <queue>
#include <cstring>

const int kMax = 500;
const int kInf = 1000000000;

struct Edge {
  int64_t src;
  int64_t dst;
  int64_t capacity;
  int64_t flow;
};

class Graph {
 private:
  std::vector<int> adj_list_[kMax];
  int current_[kMax];
  bool visited_[kMax];
  int64_t level_[kMax];
  int64_t end_;

 public:
  std::vector<Edge> edges;
  Graph(int64_t t);
  ~Graph();
  void AddEdge(int64_t vert_a, int64_t vert_b, int64_t weight);
  bool BFS();
  int64_t DFS(int64_t position, int64_t min_flow);
  int64_t FindMaxFlow();
};

Graph::Graph(int64_t t) : end_(t) {}

Graph::~Graph() {}

void Graph::AddEdge(int64_t vert_a, int64_t vert_b, int64_t weight) {
  Edge one{vert_a, vert_b, weight, 0};
  edges.push_back(one);
  Edge two{vert_a, vert_b, 0, 0};
  edges.push_back(two);
  int64_t m = edges.size();
  adj_list_[vert_a].push_back(m - 2);
  adj_list_[vert_b].push_back(m - 1);
}

bool Graph::BFS() {
  std::memset(visited_, false, sizeof(visited_));
  std::queue<int> queue;
  queue.push(1);
  level_[1] = 0;
  visited_[1] = true;
  while (!queue.empty()) {
    int vert_u = queue.front();
    queue.pop();
    for (auto i : adj_list_[vert_u]) {
      Edge& edge = edges[i];
      if (!visited_[edge.dst] && edge.capacity > edge.flow) {
        visited_[edge.dst] = true;
        level_[edge.dst] = level_[vert_u] + 1;
        queue.push(edge.dst);
      }
    }
  }
  return visited_[end_];
}

int64_t Graph::DFS(int64_t position, int64_t min_flow) {
  if (position == end_ || min_flow == 0) {
    return min_flow;
  }
  int64_t flow = 0;
  int64_t delta;
  for (auto& i : adj_list_[position]) {
    Edge& edge = edges[i];
    if (level_[edge.dst] == level_[position] + 1 && (delta = DFS(edge.dst, std::min(min_flow, edge.capacity - edge.flow))) > 0) {
      flow += delta;
      min_flow -= delta;
      edge.flow += delta;
      edges[i ^ 1].flow -= delta;
      if (min_flow == 0) {
        break;
      }
    }
  }
  return flow;
}

int64_t Graph::FindMaxFlow() {
  int64_t max_flow = 0;
  while (BFS()) {
    std::memset(current_, 0, sizeof(current_));
    while (int64_t flow = DFS(1, kInf)) {
      max_flow += flow;
    }
  }
  return max_flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL); 
  int64_t vert_num, edge_num;
  std::cin >> vert_num >> edge_num;
  Graph graph(vert_num);
  for (int64_t i = 0; i < edge_num; i++) {
    int64_t vert_a, vert_b, weight;
    std::cin >> vert_a >> vert_b >> weight;
    graph.AddEdge(vert_a, vert_b, weight);
  }
  int64_t max_flow = graph.FindMaxFlow();
  std::cout << max_flow << '\n';
  for (size_t i = 0; i < graph.edges.size(); ++i) {
    if (i % 2 == 0) {
      std::cout << graph.edges[i].flow << '\n';
    }
  } 
  return 0;
}