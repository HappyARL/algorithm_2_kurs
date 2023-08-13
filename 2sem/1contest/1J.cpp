#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Vertex {
  T root;
  T strength;
};

template <typename T>
struct Edge {
  T src_vertex;
  Vertex<T> dst_vertex;
};

template <typename T>
class DSU {
 private:
  std::vector<Vertex<T> > vertices;

 public:
  DSU(T students);
  ~DSU();
  void Unite(T student_a, T student_b, T power);
  Vertex<T> Find(T student_a);
  bool Ask(T vertex_a, T vertex_b);
};

template <typename T>
DSU<T>::DSU(T students) {
  Vertex<T> point;
  vertices.resize(students);
  for (int i = 0; i < students; ++i) {
    point.root = i;
    point.strength = 0;
    vertices[i] = point;
  }
}

template <typename T>
DSU<T>::~DSU() {}

template <typename T>
void DSU<T>::Unite(T student_a, T student_b, T power) {
  T root_a = Find(student_a).root;
  T root_b = Find(student_b).root;
  if (root_a != root_b) {
    vertices[root_b].root = root_a;
    T total_power = vertices[root_b].strength + power;
    vertices[root_a].strength += total_power;
  } else {
    vertices[root_a].strength += power;
  }
}

template <typename T>
Vertex<T> DSU<T>::Find(T student_a) {
  if (vertices[student_a].root != student_a) {
    vertices[student_a] = Find(vertices[student_a].root);
  }
  return vertices[student_a];
}

template <typename T>
bool DSU<T>::Ask(T vertex_a, T vertex_b) {
  if (Find(vertex_a).root == Find(vertex_b).root) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  DSU<int> dsu(n);

  for (int i = 0; i < m; ++i) {
    int v, u;
    cin >> v >> u;
    dsu.Unite(v - 1, u - 1, 0);
  }

  vector<int> components(n, 0);
  for (int i = 0; i < n; ++i)
    components[dsu.Find(i).root]++;

  int minAdditionalTunnels = 0;
  for (int i = 0; i < n; ++i) {
    if (components[i] > 0)
      minAdditionalTunnels += components[i] - 1;
  }

  cout << minAdditionalTunnels << endl;

  return 0;
}
