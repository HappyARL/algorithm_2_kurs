#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<size_t>> adj_list;
  size_t total_planet_num;

 public:
  Graph(size_t planet_num);
  ~Graph();
  bool Exists(size_t planet_a, size_t planet_b);
  void AddEdge(size_t planet_a, size_t planet_b);
  void BFS(size_t start, size_t finish);
};

Graph::Graph(size_t planet_num) : total_planet_num(planet_num) {
  adj_list.resize(planet_num);
}

Graph::~Graph() {}

bool Graph::Exists(size_t planet_a, size_t planet_b) {
  for (size_t i : adj_list[planet_a]) {
    if (i == planet_b)
      return true;
  }
  return false;
}

void Graph::AddEdge(size_t planet_a, size_t planet_b) {
  if (!Exists(planet_a, planet_b)) {
    adj_list[planet_a].push_back(planet_b);
    adj_list[planet_b].push_back(planet_a);
  }
}

void Graph::BFS(size_t start, size_t finish) {
  std::queue<size_t> queue;
  queue.push(start);

  std::vector<int> visited(total_planet_num, -1);
  std::vector<size_t> planets(total_planet_num);
  visited[start] = 0;

  while (!queue.empty()) {
    size_t v = queue.front();
    queue.pop();
    for (size_t u : adj_list[v]) {
      if (visited[u] == -1) {
        queue.push(u);
        visited[u] = visited[v] + 1;
        planets[u] = v;
      }
    }
  }

  if (visited[finish] == -1) {
    std::cout << -1 << std::endl;
  } else {
    size_t length = 0;
    std::vector<size_t> ans;
    while (finish != start) {
      ans.push_back(finish);
      finish = planets[finish];
      ++length;
    }
    std::cout << length << '\n';
    std::cout << start + 1 << " ";
    for (size_t i = ans.size(); i > 0; --i) {
      std::cout << ans[i - 1] + 1 << " ";
    }
  }
}

int main() {
  size_t planet_num, jump_num;
  std::cin >> planet_num >> jump_num;
  Graph graph(planet_num);
  size_t start, finish;
  std::cin >> start >> finish;
  while (jump_num != 0) {
    size_t planet_a, planet_b;
    std::cin >> planet_a >> planet_b;
    graph.AddEdge(planet_a - 1, planet_b - 1);
    --jump_num;
  }
  graph.BFS(start - 1, finish - 1);
  return 0;
}
