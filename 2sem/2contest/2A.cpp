#include <iostream>
#include <vector>
#include <set>

class Graph {
 private:

 public:
  std::vector<std::vector<std::pair<int, int> > > connections;
  Graph(int value);
  ~Graph();
  bool Exists(int vec, int index);
  void AddConnection(int point_a, int point_b, int weight);
};

Graph::Graph(int value) { connections.resize(value); }

Graph::~Graph() {}

bool Graph::Exists(int vec, int index) {
  for (size_t i = 0; i < connections[vec].size(); ++i) {
    if (connections[vec].at(i).first == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddConnection(int point_a, int point_b, int weight) {
  if (!Exists(point_a, point_b)) {
    connections[point_a].push_back(std::make_pair(point_b, weight));
    connections[point_b].push_back(std::make_pair(point_a, weight));
  }
}

class DijkstraVisitor {
 private:
  Graph graph;
  int start_point;

 public:
  DijkstraVisitor(int start_point, Graph graph);
  ~DijkstraVisitor();
  std::vector<int> Dijkstra();
};

DijkstraVisitor::DijkstraVisitor(int start, Graph main_graph) : start_point(start), graph(main_graph) {}

DijkstraVisitor::~DijkstraVisitor() {}

std::vector<int> DijkstraVisitor::Dijkstra() {
  std::vector<int> answer;
  answer.resize(graph.connections.size());
  for (size_t i = 0; i < graph.connections.size(); ++i) {
    answer[i] = 2009000999;
  }
  answer[start_point] = 0;
  std::set<std::pair<int, int> > distance;
  distance.insert(std::make_pair(answer[start_point], start_point));
  while (!distance.empty()) {
    int index = distance.begin()->second;
    distance.erase(distance.begin());
    for (size_t j = 0; j < graph.connections[index].size(); ++j) {
      int sum = answer[index] + graph.connections[index].at(j).second;
      if (sum < answer[graph.connections[index].at(j).first]) {
        distance.erase(std::make_pair(answer[graph.connections[index].at(j).first],
                                             graph.connections[index].at(j).first));
        answer[graph.connections[index].at(j).first] = sum;
        distance.insert(std::make_pair(answer[graph.connections[index].at(j).first],
                                       graph.connections[index].at(j).first));
      }
    }
  }
  return answer;
}

int main() {
  int maps;
  std::cin >> maps;
  std::vector<std::vector<int> > total_answer;
  while (maps != 0) {
    int rooms, connections;
    std::cin >> rooms >> connections;
    Graph graph(rooms);
    while (connections != 0) {
      int room_out, room_in, weight;
      std::cin >> room_out >> room_in >> weight;
      graph.AddConnection(room_out, room_in, weight);
      --connections;
    }
    int start_point;
    std::cin >> start_point;
    std::cout << std::endl;
    DijkstraVisitor dijkstra(start_point, graph);
    std::vector<int> tmp = dijkstra.Dijkstra();
    total_answer.push_back(tmp);
    --maps;
  }
  for (int i = 0; i < (int)total_answer.size(); ++i) {
    for (int j = 0; j < (int)total_answer[i].size(); ++j) {
      std::cout << total_answer[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
