#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int MAX_STATES = 1000005;
const int ALPHABET_SIZE = 26;

struct Node {
  map<char, int> next;
  int parent;
  char parentChar;
  int suffixLink;
  int outputLink;
  vector<int> patterns;

  Node(int p, char ch) : parent(p), parentChar(ch), suffixLink(-1), outputLink(-1) {}
};

vector<Node> trie(1, Node(0, 0));

void addPattern(const string &pattern, int patternIndex) {
  int nodeIndex = 0;
  for (char ch : pattern) {
    if (trie[nodeIndex].next.find(ch) == trie[nodeIndex].next.end()) {
      trie.emplace_back(nodeIndex, ch);
      trie[nodeIndex].next[ch] = trie.size() - 1;
    }
    nodeIndex = trie[nodeIndex].next[ch];
  }
  trie[nodeIndex].patterns.push_back(patternIndex);
}

void buildAhoCorasick() {
  queue<int> q;
  q.push(0);

  while (!q.empty()) {
    int currentNode = q.front();
    q.pop();

    for (const auto &[ch, nextNode] : trie[currentNode].next) {
      int linkNode = trie[currentNode].suffixLink;
      while (linkNode != -1 && trie[linkNode].next.find(ch) == trie[linkNode].next.end()) {
        linkNode = trie[linkNode].suffixLink;
      }
      if (linkNode == -1) {
        trie[nextNode].suffixLink = 0;
      } else {
        trie[nextNode].suffixLink = trie[linkNode].next[ch];
        trie[nextNode].outputLink = trie[nextNode].suffixLink;
        for (int patternIndex : trie[trie[nextNode].outputLink].patterns) {
          trie[nextNode].patterns.push_back(patternIndex);
        }
      }
      q.push(nextNode);
    }
  }
}

vector<int> searchPatterns(const string &text) {
  vector<int> result(trie.size());

  int currentNode = 0;
  for (size_t i = 0; i < text.size(); ++i) {
    while (currentNode != 0 && trie[currentNode].next.find(text[i]) == trie[currentNode].next.end()) {
      currentNode = trie[currentNode].suffixLink;
    }
    if (trie[currentNode].next.find(text[i]) != trie[currentNode].next.end()) {
      currentNode = trie[currentNode].next[text[i]];
      for (int patternIndex : trie[currentNode].patterns) {
        result[patternIndex]++;
      }
    }
  }

  return result;
}

int main() {
  string T;
  cin >> T;

  int N;
  cin >> N;

  for (int i = 0; i < N; ++i) {
    string Si;
    cin >> Si;
    addPattern(Si, i);
  }

  buildAhoCorasick();

  vector<int> patternCounts = searchPatterns(T);

  for (int count : patternCounts) {
    cout << count;
    if (count > 0) {
      for (int nodeIndex : trie[0].patterns) {
        if (trie[nodeIndex].outputLink != -1) {
          cout << " " << trie[nodeIndex].outputLink + 1;
        }
      }
    }
    cout << endl;
  }

  return 0;
}
