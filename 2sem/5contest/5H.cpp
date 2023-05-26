#include<iostream>

class TrieNode {
 public:
  TrieNode* children[26];
  bool end_of_word;
  char letter;

  TrieNode() : children() {
    end_of_word = false;
    for (auto & i : children) {
      i = nullptr;
    }
    letter = '\0';
  }
};

class Trie {
 public:
  TrieNode root;

  void Insert (std::string str) {
    TrieNode* current = &root;
    for (size_t i = 0; i < str.length(); i++) {
      int curr_letter = str.at(i)-'a';
      if (current->children[curr_letter] == nullptr) {
        current->children[curr_letter] = new TrieNode;
        current->children[curr_letter]->letter = str.at(i);
      }
      current = current->children[curr_letter];
    }
    current->end_of_word = true;
  }

  TrieNode* Search (std::string str) {
    TrieNode* current = &root;
    for (size_t i = 0; i < str.length(); i++) {
      if (current->children[str.at(i)-'a']) {
        current = current->children[str.at(i)-'a'];
      } else {
        current = nullptr;
        break;
      }
    }
    return current;
  }

  void PrintLexical (TrieNode* current, const std::string& prefix, const std::string& suffix) {
    if (current->end_of_word && !suffix.empty()) {
      std::cout << prefix+suffix << std::endl;
    }
    for (int i=0; i<26; i++) {
      std::string temp = suffix;
      if (current->children[i]) {
        temp += current->children[i]->letter;
        PrintLexical(current->children[i], prefix, temp);
      }
    }
  }
};

int main() {
  Trie T;

  std::string text;
  std::cin >> text;
  T.Insert(text);
  int64_t count;
  std::cin >> count;
  while (count != 0) {
    std::string pattern;
    std::cin >> pattern;
    TrieNode* current = T.Search(pattern);

    if (current == nullptr || current == &T.root) {
      std::cout << 0 << std::endl;
    } else {
      bool has_children = false;
      for (auto & c : current->children) {
        if (c != nullptr) {
          has_children = true; break;
        }
      }
      if (!has_children) {
        std::cout << 0 << std::endl;
      } else {
        std::cout << "contain " << pattern << std::endl;
        T.PrintLexical(current, pattern, "");
      }
    }
    --count;
  }
  return 0;
}
