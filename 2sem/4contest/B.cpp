#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int> > adj_list_;
  std::vector<int> match_;

 public:
  Graph(int vert_num, int edge_num, std::vector<std::vector<int> > edges);
  ~Graph();
  bool DFS(int vertex);
};

bool Graph::DFS(int u) {
  std::vector<int64_t> visited_(adj_list_.size(), false);
  if (visited_[u]) {
    return false;
  }
  visited_[u] = true;
  for (int v : adj_list_[u]) {
    if (match_[v] == -1 || DFS(match_[v])) {
      match_[v] = u;
      return true;
    }
  }
  return false;
}

Graph::Graph(int left_size, int right_size,
  std::vector<std::vector<int> > edges) : adj_list_(edges) {
  int ans = 0;
  match_.resize(right_size, -1);
  for (int i = 0; i < left_size; ++i) {
    if (DFS(i)) {
      ++ans;
    }
  }
  std::cout << ans << '\n';
  for (int i = 0; i < right_size; ++i) {
    if (match_[i] != -1) {
      std::cout << match_[i] + 1 << " " << i + 1 << '\n';
    }
  }
}

Graph::~Graph() {}

int main() {
  size_t english_words, chinese_words;
  std::cin >> english_words >> chinese_words;
  std::vector<std::vector<int> > edges(english_words);
  for (size_t i = 0; i < english_words; ++i) {
    size_t vert;
    std::cin >> vert;
    while (vert != 0) {
      edges[i].push_back(vert - 1);
      std::cin >> vert;
    }
  }
  Graph graph(english_words, chinese_words, edges);
  return 0;
}
