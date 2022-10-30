#include <iostream>

struct Node {
  size_t key;
  size_t height;
  Node* left;
  Node* right;
  explicit Node(size_t k) {
    key = k;
    height = 1;
    left = nullptr;
    right = nullptr;
  }
};

int Height(Node* node) {
  if (node == NULL) {
    return 0;
  }
  return node->height;
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

int GetBalance(Node* node) {
  if (node == NULL) {
    return 0;
  }
  return Height(node->left) - Height(node->right);
}

Node* Insert(Node* node, size_t key) {
  if (node == NULL) {
    return new Node(key);
  }
  if (key < node->key) {
    node->left = Insert(node->left, key);
  } else if (key > node->key) {
    node->right = Insert(node->right, key);
  } else {
    return node;
  }
  node->height = 1 + std::max(Height(node->left), Height(node->right));
  int balance = GetBalance(node);
  if (balance > 1 && key < node->left->key) {
    return RightRotate(node);
  }
  if (balance < -1 && key > node->right->key) {
    return LeftRotate(node);
  }
  if (balance > 1 && key > node->left->key) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  if (balance < -1 && key < node->right->key) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

int Next(Node* node, size_t key, size_t c) {
  if (node == nullptr) {
    return c;
  }
  if (node->key >= key && node->key < c) {
    c = node->key;
    return Next(node->left, key, c);
  }
  return Next(node->right, key, c);
  return c;
}

void Clear(Node* node) {
  if (node != nullptr && node->left != nullptr) {
    Clear(node->left);
  }
  if (node != nullptr && node->right != nullptr) {
    Clear(node->right);
  }
  delete node;
}

void preOrder(Node *root) {
  if (root != NULL) {
    std::cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Node* root = NULL;
  size_t q, y;
  std::cin >> q;
  bool flag = false;
  while (q != 0) {
    char cmd;
    size_t n;
    std::cin >> cmd >> n;
    if (cmd == '+') {
      if (flag) {
        n = (n + y) % (size_t)1e9;
        flag = false;
      }
      root = Insert(root, n);
    }
    if (cmd == '?') {
      size_t c = (size_t)1e9;
      size_t ans = Next(root, n, c);
      ans == (size_t)1e9 ? std::cout << "-1" << std::endl
                         : std::cout << ans << std::endl;
      flag = true;
      y = ans;
    }
    --q;
  }
  preOrder(root);
  Clear(root);
  return 0;
}
