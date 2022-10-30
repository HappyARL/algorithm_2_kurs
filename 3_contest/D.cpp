#include <iostream>
#include <random>

class Treap {
 public:
  bool Find(const size_t& elem) {
    return Find(root_, elem) != nullptr;
  }
  
  void Exists(const size_t& elem) {
    std::cout << Find(elem) ?  "true /n" :  "false /n";
  }

  /*void Insert(const size_t& elem) {
    if (root_ == nullptr) {
      root_->value = elem;
    }
    auto trees = Split(root_, elem);
    root_ = Merge(Merge(trees.first, new Node(elem)), trees.second);
  }*/
  void Insert(const size_t& num) {
    Node* node = new Node(num);
    size_t prior = std::rand();
    if (node != nullptr && node->priority > prior) {
        Node* current = node;
        while (current->parent != nullptr && current->priority > prior) {
          current = current->parent;
        }
        if (current->priority > prior) {
          node = new Node(num, nullptr, current);
          current->parent = node;
        } else {
          node = new Node(num, current, current->right_child);
          current->right_child->parent = node;
          current->right_child = node;
        }
      } else {
        Node* current = new Node(num, node);
        node->right_child = current;
        node = node->right_child;
      }
  }

  /*void Erase(const size_t& elem) {
    if (!Find(elem)) {
      return;
    }
    auto trees = Split(root_, elem);
    Node* node = trees.second;
    trees.second = trees.second->right;
    delete node;
    root_ = Merge(trees.first, trees.second);
  }*/

 private:
  struct Node {
    explicit Node(const size_t& mood, Node* par = nullptr, Node* left = nullptr, Node* right = nullptr) : priority(std::rand()) {
      value = mood;
      left_child = left;
      right_child = right;
      parent = par;
    }
    Node* parent = nullptr;
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    size_t value;
    size_t priority;
  };
  /*
  static std::pair<Node*, Node*> Split(Node* node, const size_t& key) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (node->value < key) {
      std::pair<Node*, Node*> split_tree = Split(node->right, key);
      Node* left_tree = node;
      left_tree->right = split_tree.first;
      return {left_tree, split_tree.second};
    }
    std::pair<Node*, Node*> split_tree = Split(node->left, key);
    Node* right_tree = node;
    right_tree->left = split_tree.second;
    return {split_tree.first, right_tree};
  }

  static Node* Merge(Node* left, Node* right) {
    if (left == nullptr && right == nullptr) {
      return nullptr;
    }
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->priority < right->priority) {
      left->right = Merge(left->right, right);
      return left;
    }
    right->left = Merge(left, right->left);
    return right;
  }
  */
  static Node* Find(Node* node, const size_t& key) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->value == key) {
      return node;
    }
    if (node->value > key) {
      return Find(node->left_child, key);
    }
    return Find(node->right_child, key);
  }

  Node* root_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Treap tp;
  size_t q;
  std::cin >> q;
  while (q != 0) {
    std::string cmd;
    size_t mood;
    std::cin >> cmd >> mood;
    if (cmd == "insert") {
      tp.Insert(mood);
    } if (cmd == "exists") {
      tp.Exists(mood);
    }
    --q;
  }
  return 0;
}