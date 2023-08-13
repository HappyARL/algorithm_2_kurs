#include <iostream>
#include <utility>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int64_t> > adj_list_;
  std::vector<int64_t> match_;
  std::vector<int64_t> visited_;

 public:
  Graph(int64_t vert_num, int64_t edge_num, std::vector<std::vector<int64_t> > edges);
  ~Graph();
  bool DFS(int64_t vertex);
};

bool Graph::DFS(int64_t u) {
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

Graph::Graph(int64_t left_size, int64_t right_size,
             std::vector<std::vector<int64_t> > edges) : adj_list_(std::move(edges)) {
  int ans = 0;
  match_.resize(right_size + left_size, -1);
  for (int64_t i = 0; i < left_size; ++i) {
    visited_.resize(left_size + right_size, false);
    if (DFS(i)) {
      ++ans;
    }
  }
  std::cout << ans << '\n';
  for (int64_t i = 0; i < right_size + left_size; ++i) {
    if (match_[i] != -1) {
      std::cout << match_[i] + 1 << " " << i - left_size + 1 << '\n';
    }
  }
}

Graph::~Graph() {}

int main() {
  int64_t english_words, chinese_words;
  std::cin >> english_words >> chinese_words;
  std::vector<std::vector<int64_t> > edges(english_words);
  for (int64_t i = 0; i < english_words; ++i) {
    int64_t vertex;
    std::cin >> vertex;
    while (vertex != 0) {
      edges[i].push_back(vertex - 1 + english_words);
      std::cin >> vertex;
    }
  }
  Graph graph(english_words, chinese_words, edges);
  return 0;
}
