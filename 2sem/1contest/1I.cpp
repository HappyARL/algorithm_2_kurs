#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

enum class Color { WHITE, GREY, BLACK };

struct Node {
  Color color = Color::WHITE;
  size_t value = 0;
  std::set<size_t> neighbours;
  size_t t_in = size_t(-1);
  size_t t_in_min = size_t(-1);
  void addNeighbour(size_t vertex) { neighbours.insert(vertex); }
};

struct Edge {
  size_t from;
  size_t to;
  size_t count;
};

class Graph {
  std::vector<Node> adj_list_;
  std::set<size_t> result_;
  std::map<std::pair<size_t, size_t>, size_t> edge_num_;

  //void updateTInMin(Node*& cur_node, size_t& counter_of_time, const size_t& iter);

  void anotherUpdateTInMin(Node*& cur_node, const size_t& iter) {
    cur_node->t_in_min =
        std::min(cur_node->t_in_min, adj_list_[iter].t_in);
  }

  void DFS(Node* cur_node, size_t& counter_of_time,
           size_t par_node = size_t(-1)) {
    cur_node->color = Color::BLACK;
    cur_node->t_in = counter_of_time;
    cur_node->t_in_min = counter_of_time;
    ++counter_of_time;
    for (const auto& neighbour : adj_list_[cur_node->value].neighbours) {
      if (neighbour != par_node) {
        if (adj_list_[neighbour].color != Color::BLACK) {
          updateTInMin(cur_node, counter_of_time, neighbour);
        } else {
          anotherUpdateTInMin(cur_node, neighbour);
        }
      }
    }
  }

 public:
  Graph(size_t vertices) : adj_list_(vertices + 1) {
    for (size_t i = 1; i <= vertices; ++i) {
      adj_list_[i].value = i;
    }
  }

  void addEdge(size_t from, size_t to, size_t count) {
    adj_list_[from].addNeighbour(to);
    adj_list_[to].addNeighbour(from);
    edge_num_.insert({{from, to}, count});
    edge_num_.insert({{to, from}, count});
  }

  void findArticulationPoints() {
    size_t counter_of_time = 0;
    for (auto& node : adj_list_) {
      if (node.color == Color::WHITE) {
        DFS(&node, counter_of_time);
      }
    }
    std::cout << result_.size() << '\n';
    for (const auto& value : result_) {
      std::cout << value << ' ';
    }
  }

  void updateTInMin(Node*& cur_node, size_t& counter_of_time,
                    const size_t& iter) {
    DFS(&adj_list_[iter], counter_of_time, cur_node->value);
    cur_node->t_in_min = std::min(cur_node->t_in_min, adj_list_[iter].t_in_min);
    std::pair<size_t, size_t> tmp = {cur_node->value, adj_list_[iter].value};
    if (adj_list_[iter].t_in_min > cur_node->t_in) {
      result_.insert(edge_num_[tmp]);
    }
  }
};

int main() {
  size_t vertexes, num_of_edges;
  std::cin >> vertexes >> num_of_edges;

  Graph graph(vertexes);

  for (size_t i = 0; i < num_of_edges; ++i) {
    size_t from, to;
    std::cin >> from >> to;
    graph.addEdge(from, to, i + 1);
  }

  graph.findArticulationPoints();
  return 0;
}
