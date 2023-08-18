#include <iostream>
#include <vector>

class LanguageGraph {
 private:
  std::vector<std::vector<int64_t> > adjList;
  std::vector<int64_t> match;
  std::vector<bool> visited;
  int64_t numLanguages;
  int64_t numWords;

 public:
  LanguageGraph(int64_t languages, int64_t words);
  ~LanguageGraph();
  bool findAugmentingPath(int64_t lang);
  void addWord(int64_t lang, int64_t word);
  void findMaxMatching();
  void printMatching();
};

LanguageGraph::LanguageGraph(int64_t languages, int64_t words) : numLanguages(languages), numWords(words) {
  adjList.resize(languages + 1);
  match.resize(words + 1, -1);
  visited.resize(languages + 1, false);
}

LanguageGraph::~LanguageGraph() = default;

bool LanguageGraph::findAugmentingPath(int64_t lang) {
  if (visited[lang]) {
    return false;
  }

  visited[lang] = true;

  for (const auto& word : adjList[lang]) {
    if (match[word] == -1 || findAugmentingPath(match[word])) {
      match[word] = lang;
      return true;
    }
  }

  return false;
}

void LanguageGraph::addWord(int64_t lang, int64_t word) {
  adjList[lang].push_back(word);
}

void LanguageGraph::findMaxMatching() {
  for (int64_t i = 1; i <= numLanguages; ++i) {
    if (findAugmentingPath(i)) {
      std::fill(visited.begin(), visited.end(), false);
    }
  }
}

void LanguageGraph::printMatching() {
  int64_t matchingCount = 0;

  for (int64_t i = 1; i <= numWords; ++i) {
    if (match[i] != -1) {
      ++matchingCount;
    }
  }

  std::cout << matchingCount << '\n';
  for (int64_t i = 1; i <= numWords; ++i) {
    if (match[i] == -1) {
      continue;
    }
    std::cout << match[i] << ' ' << i << '\n';
  }
}

int main() {
  int64_t numLanguages, numWords;
  std::cin >> numLanguages >> numWords;

  LanguageGraph graph(numLanguages, numWords);

  for (int64_t i = 1; i <= numLanguages; ++i) {
    int64_t word;
    std::cin >> word;
    while (word != 0) {
      graph.addWord(i, word);
      std::cin >> word;
    }
  }

  graph.findMaxMatching();
  graph.printMatching();

  return 0;
}
