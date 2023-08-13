#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
  int to, cap, cost, flow;
};

int n, m; // Количество городов и связей
vector<vector<int>> graph;
vector<Edge> edges;
vector<int> dist, parent, edgeIndex;

void addEdge(int from, int to, int cap, int cost) {
  graph[from].push_back(edges.size());
  edges.push_back({to, cap, cost, 0});
  graph[to].push_back(edges.size());
  edges.push_back({from, 0, -cost, 0});
}

bool BellmanFord(int source, int sink) {
  dist.assign(n + 1, INF);
  dist[source] = 0;

  for (int i = 0; i < n; ++i) {
    bool updated = false;
    for (int u = 1; u <= n; ++u) {
      for (int idx : graph[u]) {
        Edge& e = edges[idx];
        if (e.cap - e.flow > 0 && dist[u] + e.cost < dist[e.to]) {
          dist[e.to] = dist[u] + e.cost;
          parent[e.to] = u;
          edgeIndex[e.to] = idx;
          updated = true;
        }
      }
    }
    if (!updated)
      break;
  }
  return dist[sink] < INF;
}

pair<int, int> minCostMaxFlow(int source, int sink) {
  int flow = 0, cost = 0;

  while (BellmanFord(source, sink)) {
    int curFlow = INF;
    for (int u = sink; u != source; u = parent[u]) {
      int idx = edgeIndex[u];
      curFlow = min(curFlow, edges[idx].cap - edges[idx].flow);
    }

    for (int u = sink; u != source; u = parent[u]) {
      int idx = edgeIndex[u];
      edges[idx].flow += curFlow;
      edges[idx ^ 1].flow -= curFlow;
      cost += curFlow * edges[idx].cost;
    }

    flow += curFlow;
  }

  return {flow, cost};
}

int main() {
  cin >> n >> m;

  graph.assign(n + 1, vector<int>());
  parent.assign(n + 1, -1);
  edgeIndex.assign(n + 1, -1);

  for (int i = 0; i < m; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;
    addEdge(from, to, 1, cost);
    addEdge(to, from, 1, cost);
  }

  pair<int, int> result = minCostMaxFlow(1, n);

  cout << result.first << " " << result.second << "\n";

  vector<int> cutEdges;
  for (size_t idx = 0; idx < edges.size(); idx += 2) {
    if (edges[idx].flow > 0) {
      cutEdges.push_back(idx / 2 + 1);
    }
  }

  for (int edge : cutEdges) {
    cout << edge << " ";
  }

  return 0;
}
