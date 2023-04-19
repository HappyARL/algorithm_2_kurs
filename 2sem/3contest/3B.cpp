#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> roots;

 public:
  DSU(int students);
  ~DSU();
  void Unite(int student_a, int student_b);
  int Find(int student_a);
  bool Ask(int vertex_a, int vertex_b);
};

DSU::DSU(int students) {
  roots.resize(students);
  for (int i = 0; i < students; ++i) {
    roots[i] = i;
  }
}

DSU::~DSU() {}

void DSU::Unite(int student_a, int student_b) {
  int root_a = Find(student_a);
  int root_b = Find(student_b);
  if (root_a != root_b) {
    roots[root_a] = root_b;
  }
}

int DSU::Find(int student_a) {
  if (roots[student_a] != student_a) {
    return roots[student_a] = Find(roots[student_a]);
  }
  return student_a;
}

bool DSU::Ask(int vertex_a, int vertex_b) {
  if (Find(vertex_a) == Find(vertex_b)) {
    return true;
  } else {
    return false;
  }
}

struct Command {
  bool cmd;
  int vertex_a;
  int vertex_b;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);   
  int vertexs, edges, requests;
  std::cin >> vertexs >> edges >> requests;
  DSU dsu(vertexs);
  int vertex;
  while (edges != 0) {
    std::cin >> vertex >> vertex;
    --edges;
  }
  std::vector<Command> commands;
  while (requests != 0) {
    std::string cmd;
    int vertex_a, vertex_b;
    std::cin >> cmd >> vertex_a >> vertex_b;
    Command command;
    if (cmd == "ask") {
      command.cmd = false;
      command.vertex_a = vertex_a;
      command.vertex_b = vertex_b;
      commands.push_back(command);
    } else {
      command.cmd = true;
      command.vertex_a = vertex_a;
      command.vertex_b = vertex_b;
      commands.push_back(command);
    }
    --requests;
  }
  std::vector<std::string> answer;
  for (int i = (int)commands.size() - 1; i >= 0; --i) {
    Command command;
    bool cmd = commands[i].cmd;
    int vertex_a = commands[i].vertex_a;
    int vertex_b = commands[i].vertex_b;
    if (cmd) {
      dsu.Unite(vertex_a - 1, vertex_b - 1);
    } else {
      bool flag = dsu.Ask(vertex_a - 1, vertex_b - 1);
      answer.push_back(flag ? "YES" : "NO");
    }
  }
  for (size_t i = answer.size(); i >= 1; --i) {
    std::cout << answer[i - 1] << std::endl;
  }
  return 0;
}
