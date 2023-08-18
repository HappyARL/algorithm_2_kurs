#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

class TreeLCA {
 private:
  std::unordered_map<int64_t, std::vector<int64_t>> tree;
  std::vector<std::vector<int64_t>> ancestorTable;
  std::vector<int64_t> timeIn;
  std::vector<int64_t> timeOut;
  int64_t numVertices;
  int64_t timer;

 public:
  TreeLCA(int64_t vertexNum) : numVertices(vertexNum), timer(0) {
    timeIn.resize(vertexNum);
    timeOut.resize(vertexNum);
    ancestorTable.resize(vertexNum);
  }

  void addEdge(int64_t from, int64_t to) {
    tree[from].push_back(to);
    tree[to].push_back(from);
  }

  void resizeAncestorTable() {
    int64_t k = (std::log2(numVertices + 1));
    for (int64_t j = 0; j < numVertices; ++j) {
      ancestorTable.at(j).resize(k + 1);
    }
  }

  int64_t findLCA(int64_t vertex_one, int64_t vertex_two, int64_t degree) {
    if (timeIn[vertex_one] <= timeIn[vertex_two] && timeOut[vertex_one] >= timeOut[vertex_two]) {
      return vertex_one;
    }
    if (timeIn[vertex_one] >= timeIn[vertex_two] && timeOut[vertex_one] <= timeOut[vertex_two]) {
      return vertex_two;
    }
    for (int64_t i = degree; i >= 0; --i) {
      if (!(timeIn.at(ancestorTable[vertex_one][i]) <= timeIn[vertex_two] && timeOut[ancestorTable[vertex_one][i]] >= timeOut[vertex_two])) {
        vertex_one = ancestorTable[vertex_one][i];
      }
    }
    return ancestorTable[vertex_one][0];
  }

  void DFS(int64_t vertex, int64_t parent, int64_t degree, int64_t height) {
    ancestorTable[vertex][0] = parent;
    timeIn[vertex] = timer++;
    
    for (int64_t i = 0; i < degree; ++i) {
      ancestorTable[vertex][i + 1] = ancestorTable.at(ancestorTable[vertex][i])[i];
    }
    
    for (const auto& neighbor : tree[vertex]) {
      if (neighbor != parent) {
        DFS(neighbor, vertex, degree, (height + 1));
      }
    }
    
    timeOut[vertex] = timer++;
  }
};

int main() {
  int64_t numVertices, numQueries;
  std::cin >> numVertices >> numQueries;

  TreeLCA tree(numVertices);

  int64_t parent, vertex_one, vertex_two, x, y, z;
  for (int64_t i = 1; i <= numVertices - 1; ++i) {
    std::cin >> parent;
    tree.addEdge(parent, i);
  }

  std::cin >> vertex_one >> vertex_two >> x >> y >> z;

  int64_t sum = 0;
  int64_t i = (std::log2(numVertices + 1));

  tree.resizeAncestorTable();
  tree.DFS(0, 0, i, 0);
  sum = tree.findLCA(vertex_one, vertex_two, i);

  int64_t help = sum;
  for (int64_t j = 1; j < numQueries; ++j) {
    vertex_one = (x * vertex_one + y * vertex_two + z) % numVertices;
    vertex_two = (x * vertex_two + y * vertex_one + z) % numVertices;
    int64_t ans = tree.findLCA((vertex_one + help) % numVertices, vertex_two, i);
    help = ans;
    sum += ans;
  }

  std::cout << sum;
  return 0;
}
