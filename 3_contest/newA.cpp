//
// Created by Артур Кулапин on 24.10.2022.
//

#ifndef TEACHING_TREES_TREAP_H_
#define TEACHING_TREES_TREAP_H_

#include <random>
#include <utility>

template <typename T>
class Treap {
 public:
  bool Find(const T& elem) {
    return Find(root_, elem) != nullptr;
  }

  void Insert(const T& elem) {
    if (Find(elem)) {
      return;
    }
    auto trees = Split(root_, elem);
    root_ = Merge(Merge(trees.first, new Node(elem)), trees.second);
  }

  void Erase(const T& elem) {
    if (!Find(elem)) {
      return;
    }
    auto trees = Split(root_, elem);
    Node* node = trees.second;
    trees.second = trees.second->right;
    delete node;
    root_ = Merge(trees.first, trees.second);
  }

 private:
  struct Node {
    explicit Node(const T& value) : value(value), priority(std::rand()) {}

    Node* left = nullptr;
    Node* right = nullptr;
    T value;
    int priority;
  };

  static std::pair<Node*, Node*> Split(Node* node, const T& key) {
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

  static Node* Find(Node* node, const T& key) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->value == key) {
      return node;
    }
    if (node->value > key) {
      return Find(node->left, key);
    }
    return Find(node->right, key);
  }

  Node* root_;
};

#endif //TEACHING_TREES_TREAP_H_
