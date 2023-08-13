#include <iostream>
#include <vector>
#include <set>

class Graph {
 private:
  std::vector<std::vector<std::pair<int, int> > > connections_;

 public:
  Graph(int value);
  ~Graph();
  bool Exists(int vec, int index);
  void AddConnection(int point_a, int point_b, int weight);
  std::vector<int> Dijkstra(int start_point);
};

Graph::Graph(int value) {
  value = value + 1;
  connections_.resize(value);
}

Graph::~Graph() {}

bool Graph::Exists(int vec, int index) {
  for (size_t i = 0; i < connections_[vec].size(); ++i) {
    if (connections_[vec].at(i).first == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddConnection(int point_a, int point_b, int weight) {
  if (!Exists(point_a, point_b)) {
    connections_[point_a].push_back(std::make_pair(point_b, weight));
    connections_[point_b].push_back(std::make_pair(point_a, weight));
  }
}

std::vector<int> Graph::Dijkstra(int start_point) {
  std::vector<int> answer;
  answer.resize(connections_.size());
  for (size_t i = 0; i < connections_.size(); ++i) {
    answer[i] = 1000000000;
  }
  answer[start_point] = 0;
  std::set<std::pair<int,int> > distance;
  distance.insert(std::make_pair(answer[start_point], start_point));
  while (!distance.empty()) {
    int index = distance.begin()->second;
    distance.erase(distance.begin());
    for (size_t j = 0; j < connections_[index].size(); ++j) {
      int sum = answer[index] + connections_[index].at(j).second;
      if (sum < answer[connections_[index].at(j).first]) {
        distance.erase(std::make_pair(answer[connections_[index].at(j).first],
                                             connections_[index].at(j).first));
        answer[connections_[index].at(j).first] = sum;
        distance.insert(std::make_pair(answer[connections_[index].at(j).first],
                                              connections_[index].at(j).first));
      }
    }
  }
  return answer;
}
/*
int main() {
  int rooms, connections, virus;
  std::cin >> rooms >> connections >> virus;
  std::vector<int> virus_room;
  while (virus != 0) {
    int room;
    std::cin >> room;
    virus_room.push_back(room);
    --virus;
  }
  Graph graph(rooms);
  while (connections != 0) {
    int room_out, room_in, weight;
    std::cin >> room_out >> room_in >> weight;
    graph.AddConnection(room_out, room_in, weight);
    --connections;
  }
  int sus, aid;
  std::cin >> sus >> aid;
  std::vector<int> tmp = graph.Dijkstra(aid);
  bool flag = true;
  for (size_t i = 0; i < virus_room.size(); ++i) {
    if (tmp[sus] > tmp[virus_room[i]] || tmp[sus] == tmp[virus_room[i]]) {
      flag = false;
    }
  }
  if (flag) {
    std::cout << tmp[sus] << std::endl;
  } else {
    std::cout << "-1" << std::endl;
  }
  return 0;
}
*/

int main() {
  int rooms = 6, connections = 5, virus = 1;
  std::vector<int> virus_room;
  while (virus != 0) {
    virus_room.push_back(6);
    --virus;
  }
  Graph graph(rooms);
  graph.AddConnection(1,2,20);
  graph.AddConnection(2,3,2);
  graph.AddConnection(3,4,1);
  graph.AddConnection(2,5,1);
  graph.AddConnection(5,6,3);
  int sus = 4, aid = 1;
  std::vector<int> tmp = graph.Dijkstra(aid);
  bool flag = false;
  for (size_t i = 0; i < virus_room.size(); ++i) {
    if (tmp[sus] < tmp[virus_room[i]]) {
      flag = true;
    }
  }
  if (flag) {
    std::cout << tmp[sus] << std::endl;
  } else {
    std::cout << "-1" << std::endl;
  }
  return 0;
}