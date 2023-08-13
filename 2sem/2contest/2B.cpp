#include <iostream>
#include <vector>
#include <set>
#include <limits>

class Graph {
 private:
  std::vector<std::vector<std::pair<int64_t, int64_t>>> connections_;

 public:
  Graph(int64_t value);
  ~Graph();
  void AddConnection(int64_t point64_t_a, int64_t point64_t_b, int64_t weight);
  std::vector<int64_t> Dijkstra(int64_t start_point64_t);
};

Graph::Graph(int64_t value) {
  connections_.resize(value);
}

Graph::~Graph() {}

void Graph::AddConnection(int64_t point64_t_a, int64_t point64_t_b, int64_t weight) {
  connections_[point64_t_a].emplace_back(point64_t_b, weight);
  connections_[point64_t_b].emplace_back(point64_t_a, weight);
}

std::vector<int64_t> Graph::Dijkstra(int64_t start_point64_t) {
  std::vector<int64_t> answer(connections_.size(), std::numeric_limits<int64_t>::max());
  answer[start_point64_t] = 0;
  std::set<std::pair<int64_t, int64_t>> distance;
  distance.emplace(0, start_point64_t);

  while (!distance.empty()) {
    int64_t index = distance.begin()->second;
    distance.erase(distance.begin());
    for (const auto& edge : connections_[index]) {
      int64_t to = edge.first;
      int64_t weight = edge.second;
      if (answer[index] + weight < answer[to]) {
        distance.erase(std::make_pair(answer[to], to));
        answer[to] = answer[index] + weight;
        distance.emplace(answer[to], to);
      }
    }
  }
  return answer;
}

int main() {
  int64_t rooms, connections, virus;
  std::cin >> rooms >> connections >> virus;
  std::vector<int64_t> virus_room(virus);
  for (int64_t i = 0; i < virus; ++i) {
    std::cin >> virus_room[i];
  }
  Graph graph(rooms + 1);
  while (connections != 0) {
    int64_t room_out, room_in, weight;
    std::cin >> room_out >> room_in >> weight;
    graph.AddConnection(room_out, room_in, weight);
    --connections;
  }
  int64_t sus, aid;
  std::cin >> sus >> aid;
  std::vector<int64_t> tmp = graph.Dijkstra(aid);
  bool flag = true;
  for (int64_t room : virus_room) {
    if (tmp[sus] >= tmp[room]) {
      flag = false;
      break;
    }
  }
  if (flag) {
    std::cout << tmp[sus] << std::endl;
  } else {
    std::cout << "-1" << std::endl;
  }
  return 0;
}
