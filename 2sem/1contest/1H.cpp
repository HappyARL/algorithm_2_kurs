// original - emax(https://www.youtube.com/watch?v=dQw4w9WgXcQ)

#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int64_t> > adj_list;
  std::vector<bool> used;
  std::vector<int64_t> t_in;
  std::vector<int64_t> f_up;
  std::vector<int64_t> answer;
  int64_t timer;

 public:
  Graph(int64_t vertices) : timer(0) {
    adj_list.resize(vertices);
    used.resize(vertices, false);
    t_in.resize(vertices);
    f_up.resize(vertices);
  }

  bool exists(int64_t from, int64_t to) {
    for (const auto& iter : adj_list[from]) {
      if (iter == to) return true;
    }
    return false;
  }

  void addEdge(int64_t from, int64_t to) {
    if (!exists(from, to)) {
      adj_list[from].push_back(to);
      adj_list[to].push_back(from);
    }
  }

  void DFS(int64_t vertex, int64_t pos = -1) {
    used[vertex] = true;
    t_in[vertex] = f_up[vertex] = timer++;

    int64_t children = 0;

    for (size_t i = 0; i < adj_list[vertex].size(); ++i) {
      int64_t to = adj_list[vertex][i];
      if (to == pos)  continue;
      if (!used[to]) {
        DFS (to, vertex);
        f_up[vertex] = std::min(f_up[vertex], f_up[to]);
        if (f_up[to] >= t_in[vertex] && pos != -1) {
          answer.push_back(vertex + 1);
        }
        ++children;
      }
      f_up[vertex] = std::min(f_up[vertex], t_in[to]);
    }

    if (pos == -1 && children > 1) {
      answer.push_back(vertex + 1);
    }
  }

  void printAnswer() {
    std::sort(answer.begin(), answer.end());

    std::cout << answer.size() << '\n';

    for (long long iter : answer) {
      std::cout << iter << '\n';
    }
  }
};

int main() {
  int64_t vertex_num, edge_num;
  std::cin >> vertex_num >> edge_num;

  Graph graph(vertex_num);

  while (edge_num != 0) {
    int64_t from_ver, to_ver;
    std::cin >> from_ver >> to_ver;

    graph.addEdge(from_ver - 1, to_ver - 1);

    --edge_num;
  }

  graph.DFS(0);

  graph.printAnswer();

  return 0;
}
