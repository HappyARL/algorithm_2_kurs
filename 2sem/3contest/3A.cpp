#include <iostream>
#include <vector>

template <typename T>
struct Vertex {
  T root;
  T strength;
};

template <typename T>
class DSU {
 private:
  std::vector<Vertex<T> > verteces;

 public:
  DSU(T students);
  ~DSU();
  void Unite(T student_a, T student_b, T power);
  Vertex<T> Find(T student_a);
  T FriendshipPower(T studen_a);
};

template <typename T>
DSU<T>::DSU(T students) {
  Vertex<T> point;
  verteces.resize(students);
  for (int i = 0; i < students; ++i) {
    point.root = i;
    point.strength = 0;
    verteces[i] = point;
  }
}

template <typename T>
DSU<T>::~DSU() {}

template <typename T>
void DSU<T>::Unite(T student_a, T student_b, T power) {
  T root_a = Find(student_a).root;
  T root_b = Find(student_b).root;
  if (root_a != root_b) {
    verteces[root_b].root = root_a;
    T total_power = verteces[root_b].strength + power;
    verteces[root_a].strength += total_power;
  } else {
    verteces[root_a].strength += power;
  }
}

template <typename T>
Vertex<T> DSU<T>::Find(T student_a) {
  if (verteces[student_a].root != student_a) {
    verteces[student_a] = Find(verteces[student_a].root);
  }
  return verteces[student_a];
}

template <typename T>
T DSU<T>::FriendshipPower(T student_a) {
  Vertex<T> leader = Find(student_a);
  return leader.strength;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL); 
  int students, friendship;
  std::cin >> students >> friendship;
  DSU<int64_t> dsu(students);
  while (friendship != 0) {
    int cmd;
    std::cin >> cmd;
    if (cmd == 1) {
      int64_t student_a, student_b, power;
      std::cin >> student_a >> student_b >> power;
      dsu.Unite(student_a - 1, student_b - 1, power);
    }
    if (cmd == 2) {
      int64_t student_a;
      std::cin >> student_a;
      std::cout << dsu.FriendshipPower(student_a - 1) << '\n';
    }
    --friendship;
  }
  return 0;
}
