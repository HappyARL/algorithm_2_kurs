#include <iostream>
#include <vector>

struct Edge {
  int64_t to;
  int64_t capacity;
  int64_t flow;

  Edge(int64_t ver_to, int64_t cap, int64_t flow) : to(ver_to),
                                                    capacity(cap),
                                                    flow(flow) {}
};

class Graph {
 private:
  std::vector<std::vector<Edge> > adj_list_;
  int64_t vertices_num;

 public:
  Graph(int64_t vertices);
  ~Graph();
  void addEdge(int64_t ver_from, int64_t ver_to, int64_t weight);
};

int main() {
  int64_t vertices, edges;
  std::cin >> vertices >> edges;

}