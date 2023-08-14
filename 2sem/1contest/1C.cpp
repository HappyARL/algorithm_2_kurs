#include <iostream>
#include <vector>

enum Color { WHITE, GREY, BLACK };

struct Node {
  Color color = Color::WHITE;
  int64_t value = 0;
  std::vector<int64_t> neighbour;
  
  void addNeighbour(const int64_t& vertex) { neighbour.push_back(vertex - 1); }
};

struct Edge {
  int64_t from;
  int64_t to;
};

class Graph {
 private:
  std::vector<Node> adj_list_;
  std::vector<int64_t> result_;
  int64_t vertices_num;

 public:
  Graph(const int64_t& vertices, const std::vector<Edge>& edges);
  ~Graph();
  void DFS(Node* cur_node, bool& found_loop, int64_t& loop_start, std::vector<int64_t>& loop);
  bool HaveLoop(std::vector<int64_t>& res);
  void printCycle();
};

Graph::Graph(const int64_t& vertices, const std::vector<Edge>& edges) : vertices_num(vertices) {
  adj_list_.resize(vertices);
  for (const auto& iter : edges) {
    adj_list_[iter.from - 1].value = iter.from - 1;
    adj_list_[iter.from - 1].addNeighbour(iter.to);
  }
}

Graph::~Graph() = default;

void Graph::DFS(Node* cur_node, bool& found_loop, int64_t& loop_start, std::vector<int64_t>& loop) {
  if (cur_node->color == Color::GREY) {
    found_loop = true;
    loop_start = cur_node->value;
    return;
  }

  cur_node->color = Color::GREY;
  for (const auto& i : cur_node->neighbour) {
    if (adj_list_[i].color != Color::BLACK) {
      DFS(&adj_list_[i], found_loop, loop_start, loop);
      if (found_loop) {
        loop.push_back(i + 1);
        if (cur_node->value == loop_start) {
          result_ = loop;
        }
        return;
      }
      adj_list_[i].color = Color::BLACK;
    }
  }

  cur_node->color = Color::BLACK;
}

bool Graph::HaveLoop(std::vector<int64_t>& res) {
  std::vector<int64_t> tmp_way;
  bool found_loop = false;
  int64_t loop_start;

  for (auto& iter : adj_list_) {
    if (iter.color == Color::WHITE) {
      DFS(&iter, found_loop, loop_start, tmp_way);
      if (found_loop) {
        res = result_;
        return true;
      }
    }
  }

  return false;
}

void Graph::printCycle() {
  std::vector<int64_t> res;
  bool have_loop = HaveLoop(res);

  if (!have_loop) {
    std::cout << "NO" << '\n';
    return;
  }
  
  std::cout << "YES" << '\n';
  for (int i = res.size() - 1; i >= 0; --i) {
    std::cout << res[i] << ' ';
  }
}

int main() {
  int64_t vertices_num, edges_num;
  std::cin >> vertices_num >> edges_num;
  
  std::vector<Edge> edges(edges_num);
  
  for (int64_t i = 0; i < edges_num; ++i) {
    std::cin >> edges[i].from >> edges[i].to;
    if (edges[i].from == edges[i].to) {
      std::cout << "YES" << '\n';
      std::cout << edges[i].from << " " << edges[i].to;
      return 0;
    }
  }

  Graph graph(vertices_num, edges);
  
  graph.printCycle();

  return 0;
}