#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

struct Edge {
  int64_t to;
  int64_t weight;
  int64_t cost;

  Edge(int64_t ver_to, int64_t ver_weight, int64_t ver_cost)
      : to(ver_to), weight(ver_weight), cost(ver_cost) {}
};

class Graph {
 private:
  std::vector<std::vector<Edge>> adj_list_;
  std::vector<int64_t> answer;
  std::vector<int64_t> time_request;
  int64_t vertices_num;

 public:
  Graph(int64_t value);
  void addEdge(int64_t point_a, int64_t point_b, int64_t weight, int64_t time);
  void Dijkstra(int64_t start_point, int64_t max_time);
  void printPath(std::vector<int64_t> prev, int64_t max_time);
};

Graph::Graph(int64_t value) : vertices_num(value) {
  adj_list_.resize(value);
  answer.resize(value, std::numeric_limits<int64_t>::max());
  time_request.resize(value, std::numeric_limits<int64_t>::max());
}

void Graph::addEdge(int64_t point_a, int64_t point_b, int64_t weight, int64_t time) {
  adj_list_[point_a].emplace_back(point_b, weight, time);
  adj_list_[point_b].emplace_back(point_a, weight, time);
}

void Graph::Dijkstra(int64_t start_point, int64_t max_time) {
  std::vector<int64_t> prev(vertices_num, -1);
  answer[start_point] = 0;
  time_request[start_point] = 0;

  std::set<std::pair<int64_t, int64_t>> distance;
  distance.insert(std::make_pair(answer[start_point], start_point));

  while (!distance.empty()) {
    int64_t index = distance.begin()->second;
    distance.erase(distance.begin());

    for (const Edge& edge : adj_list_[index]) {
      int64_t neighbor = edge.to;
      int64_t weight = edge.weight;
      int64_t cost = edge.cost;

      int64_t sum = answer[index] + weight;
      int64_t total_time = time_request[index] + cost;

      if (sum < answer[neighbor] && total_time <= max_time) {
        distance.erase(std::make_pair(answer[neighbor], neighbor));
        answer[neighbor] = sum;
        time_request[neighbor] = total_time;
        prev[neighbor] = index;
        distance.insert(std::make_pair(answer[neighbor], neighbor));
      }
    }
  }

  printPath(prev, max_time);
}

void Graph::printPath(std::vector<int64_t> prev, int64_t max_time) {
  std::vector<int64_t> path;
  int64_t current_vertex = vertices_num - 1;

  while (current_vertex != -1) {
    path.push_back(current_vertex);
    current_vertex = prev[current_vertex];
  }
  std::reverse(path.begin(), path.end());

  if (time_request[vertices_num - 1] > max_time) {
    std::cout << "-1" << '\n';
    return;
  }

  int64_t total_time = time_request[vertices_num - 1];
  if (total_time > max_time) {
    std::cout << "-1" << '\n';
    return;
  }

  std::cout << answer[vertices_num - 1] << '\n';
  std::cout << path.size() << '\n';

  for (const auto& iter : path) {
    std::cout << iter + 1 << " ";
  }
}

int main() {
  int64_t vertices, edges, max_time;
  std::cin >> vertices >> edges >> max_time;

  Graph graph(vertices);

  while (edges != 0) {
    int64_t ver_a, ver_b, weight, time;
    std::cin >> ver_a >> ver_b >> weight >> time;
    graph.addEdge(ver_a - 1, ver_b - 1, weight, time);
    --edges;
  }

  graph.Dijkstra(0, max_time);

  return 0;
}
