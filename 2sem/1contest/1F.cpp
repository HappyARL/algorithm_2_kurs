#include <iostream>
#include <vector>
#include <stack>

void DFS(int64_t v, std::vector<bool>& visited, std::vector<std::vector<int64_t>>& adj_list, std::stack<int64_t>& order) {
  visited[v] = true;
  for (int64_t neighbor : adj_list[v]) {
    if (!visited[neighbor]) {
      DFS(neighbor, visited, adj_list, order);
    }
  }
  order.push(v);
}

void DFS_REVERSE(int64_t v, int64_t component_id, std::vector<bool>& visited, std::vector<std::vector<int64_t>>& reversed_adj_list, std::vector<int64_t>& components) {
  visited[v] = true;
  components[v] = component_id;
  for (int64_t neighbor : reversed_adj_list[v]) {
    if (!visited[neighbor]) {
      DFS_REVERSE(neighbor, component_id, visited, reversed_adj_list, components);
    }
  }
}

int main() {
  int64_t vertices, edges;
  std::cin >> vertices >> edges;

  std::vector<std::vector<int64_t>> adj_list(vertices + 1);
  std::vector<std::vector<int64_t>> reversed_adj_list(vertices + 1);
  while (edges != 0) {
    int64_t start, end;
    std::cin >> start >> end;
    adj_list[start].push_back(end);
    reversed_adj_list[end].push_back(start);
    --edges;
  }

  std::vector<bool> visited(vertices + 1, false);
  std::stack<int64_t> order;

  for (int64_t i = 1; i <= vertices; ++i) {
    if (!visited[i]) {
      DFS(i, visited, adj_list, order);
    }
  }

  visited.assign(vertices + 1, false);
  std::vector<int64_t> components(vertices + 1, 0);
  int64_t component_id = 1;

  while (!order.empty()) {
    int64_t v = order.top();
    order.pop();
    if (!visited[v]) {
      DFS_REVERSE(v, component_id, visited, reversed_adj_list, components);
      ++component_id;
    }
  }

  std::cout << component_id - 1 << '\n';
  for (int64_t i = 1; i <= vertices; ++i) {
    std::cout << components[i] << " ";
  }
  std::cout << '\n';

  return 0;
}
