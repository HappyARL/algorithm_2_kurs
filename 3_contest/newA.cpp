#include <iostream>

class Treap {
 public:
 void Insert(int num, int prior) {
   Node* T;
   T->num = num;
   T->prior = prior;
   std::pair<Node*, Node*> trees = Split(root_, prior);
   root_ = Merge(Merge(trees.first, T), trees.second);
 }
 void TrepPrint() {
   Print(root_);  
 }
 private:
  struct Node {
    explicit Node(const int num, const int prior) {}
    Node* left = nullptr;
    Node* right = nullptr;
    int num;
    int prior;
  };
  
  Node* root_;
  
  std::pair<Node*, Node*> Split(Node* node, int key) {
    if(node == nullptr) {
      return {nullptr, nullptr};
    }
    if(node->prior < key) {
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

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr && right == nullptr) {
      return nullptr;
    }
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->num < right->num) {
      left->right = Merge(left->right, right);
      return left;
    }
    right->left = Merge(left, right->left);
    return right;
  }

  Node* Print(Node* node) {
    bool right = 1, left = 1;
    if (node == nullptr) {
      return node;
    }
    if (node->left == nullptr) {
      node->left->num = 0;
      left = 0;
    }
    if (node->right == nullptr) {
      node->left->num = 0;
      right = 0;
    }
    std::cout << node->num << node->left->num << node->right->num << std::endl;
    if (left) {
      return Print(node->left);
    }
    if (right) {
      return Print(node->right);
    }
  }
};

int main() {
  Treap tp;
  int N;
  std::cin >> N;
  while (N != 0) {
    int num, priority;
    std::cin >> num >> priority;
    tp.Insert(num, priority);
    --N;
  }
  tp.TrepPrint();
}