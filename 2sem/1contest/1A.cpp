#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<int> result;
  std::vector<std::vector<int> > adj_list;
  std::vector<bool> visited;

 public:
  Graph(int planets);
  ~Graph();
  bool Exists(int vec, int index);
  void AddConnection(int up, int down);
  void DFS(int start, int end);
  void Print();
};

Graph::Graph(int planets) {
  result = std::vector<int> ();
  adj_list.resize(planets);
  visited.resize(planets);
}

Graph::~Graph() {}

bool Graph::Exists(int vec, int index) {
  for (size_t i = 0; i < adj_list[vec].size(); ++i) {
    if (adj_list[vec].at(i) == index) {
      return true;
    }
  }
  return false;
}

void Graph::AddConnection(int up, int down) {
  int index_up = up - 1;
  int down_index = down - 1;
  if (!Exists(index_up, down)) {
    adj_list[index_up].push_back(down);
    adj_list[down_index].push_back(up);
  }
}
// write bfs instead of dfs
void Graph::DFS(int start, int end) {
  int i = start - 1;
  if (visited[i]) {
    return;
  }
  visited[i] = true;
  result.push_back(start);
  for (size_t j = 0; j < adj_list[i].size(); ++j) {
    if (adj_list[i].at(j) == end) {
      result.push_back(end);
      return;
    } else {
      int index = adj_list[i].at(j) - 1;
       if (!visited[index]) {
        DFS(adj_list[i].at(j), end);  
       }
    }    
  }
}

void Graph::Print() {
  if (result.size() == 0) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << result.size() - 1 << std::endl;
    int index = 0;
    while (index < result.size()) {
      std::cout << result[index] << " ";
      ++index;
    }
    std::cout << std::endl;
  }
}

int main() {
  int planets, jumps;
  std::cin >> planets >> jumps;
  int start, end;
  std::cin >> start >> end;
  Graph graph(planets);
  while (jumps != 0) {
    int up, down;
    std::cin >> up >> down;
    graph.AddConnection(up, down);
    --jumps;
  }
  std::cout << "inserft DONE" << std::endl;
  graph.DFS(start - 1, end - 1);
  std::cout << "dfs DONE" << std::endl;
  graph.Print();
  std::cout << "print DONE" << std::endl;
  return 0;
}


// vector of vecrot like hashmap with buckeatsa but without hashfuncßß
/*

const int kLength = 2e5 + 5;

class Stack {
 private:
  int top_;
  int* main_arr_;

 public:
  Stack();
  ~Stack();
  void Push(int value);
  void Pop();
  void Print();
};

Stack::Stack() {
  top_ = 0;
  main_arr_ = new int[kLength];
}

Stack::~Stack() {
  delete[] main_arr_;
}

void Stack::Push(int value) {
  top_++;
  main_arr_[top_] = value;
}

void Stack::Pop() {
  if (top_ == 0) {
    std::cout << "error" << std::endl;
  } else {
    int pop_value = main_arr_[top_];
    top_--;
  }
}

void Stack::Print() {
  if (top_ == 0) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << top_ - 1 << std::endl;
    int index = 0;
    while (index < top_) {
      std::cout << main_arr_[index] << " ";
      ++index;
    }
    std::cout << std::endl;
  }
}
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-

int main() {
  int planets = 4;
  int jumps = 5;
  int start = 1;
  int end = 4;
  Graph gr(planets);
  gr.AddConnection(1, 3);
  gr.AddConnection(3, 2);
  gr.AddConnection(2, 4);
  gr.AddConnection(2, 1);
  gr.AddConnection(2, 3);
  gr.DFS(start, end);
  gr.Print();
  return 0;
}
*/
