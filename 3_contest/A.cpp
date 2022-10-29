#include <iostream>

class Treap {
 private:
  struct Node {
    int num, priority, count;
    Node* parent;
    Node* left_child;
    Node* right_child;
    explicit Node(int k, int prior, Node* par = nullptr, Node* left = nullptr,
                  Node* right = nullptr) {
      count = 0;
      num = k;
      priority = prior;
      left_child = left;
      right_child = right;
      parent = par;
    }
  };
 public:
  Node* treap;
  Node* GetRoot(Node* node) {
    while (node != nullptr && node->parent != nullptr) {
      node = node->parent;
    }
    return node;
  }

  Node* MakeTree(size_t n) {
    Node* node = nullptr;
    int num, prior;
    std::cin >> num >> prior;
    node = new Node(num, prior);
    ++node->count;
    for (size_t i = 1; i < n; ++i) {
      std::cin >> num >> prior;
      if (node != nullptr && node->priority > prior) {
        Node* current = node;
        while (current->parent != nullptr && current->priority > prior) {
          current = current->parent;
        }
        if (current->priority > prior) {
          node = new Node(num, prior, nullptr, current);
          current->parent = node;
          node->count = i + 1;
        } else {
          node = new Node(num, prior, current, current->right_child);
          current->right_child->parent = node;
          current->right_child = node;
          node->count = i + 1;
        }
      } else {
        Node* current = new Node(num, prior, node);
        node->right_child = current;
        node = node->right_child;
        node->count = i + 1;
      }
    }
    return GetRoot(node);
  }

  void PrintTree(Node* node) {
    if (node != nullptr && node->left_child != nullptr) {
      PrintTree(node->left_child);
    }
    if (node->parent != nullptr) {
      std::cout << node->parent->count << " ";
    } else {
      std::cout << 0 << " ";
    }
    if (node->left_child != nullptr) {
      std::cout << node->left_child->count << " ";
    } else {
      std::cout << 0 << " ";
    }
    if (node->right_child != nullptr) {
      std::cout << node->right_child->count << " ";
    } else {
      std::cout << 0 << " ";
    }
    std::cout << std::endl;
    if (node != nullptr && node->right_child != nullptr) {
      PrintTree(node->right_child);
    }
  }

  void Clear(Node* node) {
    if (node != nullptr && node->left_child != nullptr) {
      Clear(node->left_child);
    }
    if (node != nullptr && node->right_child != nullptr) {
      Clear(node->right_child);
    }
    delete node;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t q;
  std::cin >> q;
  Treap tp;
  tp.treap = tp.MakeTree(q);
  std::cout << "YES" << std::endl;
  tp.PrintTree(tp.treap);
  tp.Clear(tp.treap);
}
