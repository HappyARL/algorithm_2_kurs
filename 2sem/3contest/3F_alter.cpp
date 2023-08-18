#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

std::vector<int64_t> t_in;
std::vector<int64_t> t_out;
std::vector<int64_t> depth;
int64_t timer = 0;
std::vector<std::vector<int64_t>> table;
std::unordered_map<int64_t, std::vector<int64_t>> graph;
std::vector<int64_t> digits;


int64_t LCA(int64_t ver1, int64_t ver2, int64_t degree) {
  if (t_in.at(ver1) <= t_in.at(ver2) && t_out.at(ver1) >= t_out.at(ver2)) {
    return ver1;
  }
  if (t_in.at(ver1) >= t_in.at(ver2) && t_out.at(ver1) <= t_out.at(ver2)) {
    return ver2;
  }
  for (int64_t i = degree; i >= 0; --i) {
    if (!(t_in.at(table.at(ver1).at(i)) <= t_in[ver2] && t_out[table.at(ver1).at(i)] >= t_out[ver2])) {
      ver1 = table.at(ver1).at(i);
    }
  }
  return table.at(ver1).at(0);
}

void DFS(int64_t vertex, int64_t par, int64_t degree, int64_t h) {
  //depth.at(vertex) = h;
  table.at(vertex).at(0) = par;
  t_in[vertex] = timer++;
  for (int64_t i = 0; i < degree; ++i) {
    table.at(vertex).at(i + 1) = table.at(table.at(vertex).at(i)).at(i);
  }
  for (const auto& it : graph[vertex]) {
    if (it == par) {
      continue;
    }
    else {
      DFS(it, vertex, degree, (h + 1));
    }
  }
  t_out[vertex] = timer++;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n, m, ver1, ver2, x, y, z;
  std::cin >> n >> m;
  t_in.resize(n);
  t_out.resize(n);
  table.resize(n);
  //depth.resize(n);
  for (int64_t i = 1; i <= n - 1; ++i) {
    std::cin >> ver1;
    graph[ver1].push_back(i);
    graph[i].push_back(ver1);
  }
  std::cin >> ver1 >> ver2 >> x >> y >> z;
  int64_t sum = 0;
  int64_t i;
  i = (std::log2(n + 1));
  for (int64_t j = 0; j < n; ++j) {
    table.at(j).resize(i + 1);
  }
  DFS(0, 0, i, 0);
  sum = 0;
  sum = LCA(ver1, ver2, i);
  int64_t help = sum;
  for (int64_t j = 1; j < m; ++j) {
    ver1 = (x * ver1 + y * ver2 + z) % n;
    ver2 = (x * ver2 + y * ver1 + z) % n;
    int64_t ans = LCA((ver1 + help) % n, ver2, i);
    help = ans;
    sum += ans;
  }
  std::cout << sum;
  return 0;
}
