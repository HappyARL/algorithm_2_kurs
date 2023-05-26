//
// Created by Арлан on 25.05.2023.
//

#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct Edge {
  int to_;
  T weigth_;
  Edge(int to, int weight) : to_(to), weigth_(weight) {}
  ~Edge() {}
};

template <typename T>
class Graph {
 private:
  int k;
  std::vector<std::vector<Edge<T> > > adj_list;
  std::vector<std::queue<int> > queue;

 public:
  Graph(int k_max, int n, int m) : k(k_max) {
    adj_list.resize(n);
    queue.resize((n - 1) * k);
  }

  ~Graph() {}

  void addEdge(int from, int to, T weigth) {
    adj_list[from].push_back(Edge<T>(to, weigth));
  }

  void BFS(int start) {
    std::vector<int> dist(adj_list.size(), INT_MAX);
    std::vector<bool> used((int)adj_list.size(), false);
    dist[start] = 0;
    queue[0].push(start);
    for (int d = 0; d < k * (int)adj_list.size(); ++d) {
      while (!queue[d].empty()) {
        int v = queue[d].front();
        queue[d].pop();
        if (used[v]) {
          continue;
        }
        used[v] = true;
        for (Edge<T>& e : adj_list[v]) {
          int to = e.to_;
          if (dist[to] <= dist[v] + e.weigth_) {
            continue;
          }
          dist[to] = dist[v] + e.weigth_;
          queue[dist[to]].push(to);
        }
      }
    }
  }

  void print() {
    for (int i = 0; i < queue.size(); ++i) {
      std::cout << i << " " << queue[i].front() << '\n';
    }
  }
};

int main() {
  int k_max, n, m;
  std::cout << "Insert value K for max weight: " ;
  std::cin >> k_max;
  std::cout << "Insert value N for vertices and edges amount: " ;
  std::cin >> n >> m;
  Graph<int> graph(k_max, n, m);
  //for (int i = 0; i < m; ++i) {
    //int from, to;
    //int weigth;
    //std::cin >> from >> to >> weigth;
    //graph.addEdge(from, to, weigth);
  //}
  graph.addEdge(0,1,2);
  graph.addEdge(1,2,3);
  graph.addEdge(0,3,1);
  graph.addEdge(3,4,4);
  graph.addEdge(3,5,5);
  graph.BFS(0);
  graph.print();
  return 0;
}
