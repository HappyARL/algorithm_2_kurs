#include <iostream>
#include <string>
#include <vector>

struct Node {
  std::string& key;
  std::string& val;
  int height;
  Node* left = nullptr;
  Node* right = nullptr;
};

int Height(Node* node) {
  if (node == NULL) {
    return 0;
  }
  return node->height;
}

int Bfactor(Node* p) { return Height(p->right) - Height(p->left); }

void FixHeight(Node* p) {
  int hl = Height(p->left);
  int hr = Height(p->right);
  p->height = (hl > hr ? hl : hr) + 1;
}

Node* RightRotate(Node* y) {
  Node* x = y->left;
  Node* z = x->right;
  x->right = y;
  y->left = z;
  y->height = std::max(Height(y->left), Height(y->right)) + 1;
  x->height = std::max(Height(x->left), Height(x->right)) + 1;
  return x;
}

Node* LeftRotate(Node* x) {
  Node* y = x->right;
  Node* z = y->left;
  y->left = x;
  x->right = z;
  x->height = std::max(Height(x->left), Height(x->right)) + 1;
  y->height = std::max(Height(y->left), Height(y->right)) + 1;
  return y;
}

Node* Balance(Node* p) {
  FixHeight(p);
  if (Bfactor(p) == 2) {
    if (Bfactor(p->right) < 0) p->right = RightRotate(p->right);
    return LeftRotate(p);
  }
  if (Bfactor(p) == -2) {
    if (Bfactor(p->left) > 0) p->left = LeftRotate(p->left);
    return RightRotate(p);
  }
  return p;
}

Node* Insert(Node* node, std::string& key, std::string& value) {
  if (node == nullptr) {
    Node* new_node = new Node{key, value, 1};
    return new_node;
  }
  int cmp = key.compare(node->key);
  if (cmp == 0) {
    return node;
  }
  if (cmp < 0) {
    node->left = Insert(node->left, key, value);
  } else {
    node->right = Insert(node->right, key, value);
  }
  return Balance(node);
}

std::string Find(Node* node, std::string key) {
  if (node == nullptr) {
    return " ";
  }
  int cmp = key.compare(node->key);
  if (cmp == 0) {
    return node->val;
  }
  if (cmp < 0) {
    return Find(node->left, key);
  } else {
    return Find(node->right, key);
  }
}

void Clear(Node* node) {
  if (node == nullptr) {
    return;
  }
  Clear(node->left);
  Clear(node->right);
  delete node;
}

int main() {
  int n;
  std::cin >> n;
  std::string key;
  std::vector<std::string> str(n * 2);
  std::cin >> str[0] >> str[1];
  Node* node = new Node{str[0], str[1], 1};
  node = Insert(node, str[1], str[0]);
  for (int i = 1; i < n; i++) {
    std::cin >> str[i * 2] >> str[i * 2 + 1];
    node = Insert(node, str[i * 2], str[i * 2 + 1]);
    node = Insert(node, str[i * 2 + 1], str[i * 2]);
  }
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> key;
    std::cout << Find(node, key) << std::endl;
  }
  Clear(node);
  return 0;
}