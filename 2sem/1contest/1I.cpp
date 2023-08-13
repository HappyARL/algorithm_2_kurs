#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
  int V;
  vector<vector<int>> adj;

 public:
  Graph(int v) : V(v), adj(v) {}

  void addEdge(int u, int v) {
    adj[u].push_back(v);
  }

  void DFS(int v, vector<bool>& visited, stack<int>& stack) {
    visited[v] = true;

    for (int i : adj[v]) {
      if (!visited[i])
        DFS(i, visited, stack);
    }

    stack.push(v);
  }

  void getSCCs(vector<vector<int>>& sccs) {
    vector<bool> visited(V, false);
    stack<int> stack;

    for (int i = 0; i < V; ++i) {
      if (!visited[i])
        DFS(i, visited, stack);
    }

    Graph reversed(V);

    for (int i = 0; i < V; ++i) {
      for (int j : adj[i])
        reversed.addEdge(j, i);
    }

    visited.assign(V, false);

    while (!stack.empty()) {
      int v = stack.top();
      stack.pop();

      if (!visited[v]) {
        vector<int> scc;
        reversed.DFS(v, visited, scc);
        sccs.push_back(scc);
      }
    }
  }
};

int main() {
  int N, M;
  cin >> N >> M;

  Graph g(N);

  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u - 1, v - 1);
  }

  vector<vector<int>> sccs;
  g.getSCCs(sccs);

  vector<bool> canMakeOneWay(M, true);

  for (const vector<int>& scc : sccs) {
    if (scc.size() > 1) {
      for (int v : scc)
        canMakeOneWay[v] = false;
    }
  }

  int count = 0;
  for (int i = 0; i < M; ++i) {
    if (!canMakeOneWay[i])
      count++;
  }

  cout << count << endl;

  for (int i = 0; i < M; ++i) {
    if (!canMakeOneWay[i])
      cout << i + 1 << " ";
  }

  return 0;
}
