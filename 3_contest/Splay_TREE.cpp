#include <iostream>
#include <vector>

struct Node {
  std::string key;
  Node* left;
  Node* right;
  explicit Node(std::string name) {
    key = name;
    left = nullptr;
    right = nullptr;
  }
};

Node* RightRotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  y->right = x;
  return y;
}

Node* LeftRotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  y->left = x;
  return y;
}

Node* Splay(Node* root, std::string key) {
  if (root == NULL || root->key == key) {
    return root; 
  }
  if (root->key > key) {
    if (root->left == NULL) {
      return root;
    }
    if (root->left->key > key) {
      root->left->left = Splay(root->left->left, key);
      root = RightRotate(root);
    } else if (root->left->key < key) {
      root->left->right = Splay(root->left->right, key);
      if (root->left->right != NULL) {
        root->left = LeftRotate(root->left);
      }
    }
    return (root->left == NULL)? root: RightRotate(root);
  } else {
    if (root->right == NULL) {
      return root;
    }
    if (root->right->key > key) {
      root->right->left = Splay(root->right->left, key);
      if (root->right->left != NULL) {
        root->right = RightRotate(root->right);
      }
    } else if (root->right->key < key) {
      root->right->right = Splay(root->right->right, key);
      root = LeftRotate(root);
    }
    return (root->right == NULL)? root: LeftRotate(root);
  }
}

Node* Search(Node* root, std::string key) {
  return Splay(root, key);
}

void preOrder(Node* root) {
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
  size_t q;
  std::cin >> q;
  std::vector<std::pair<std::string, std::string>> arr;
  for (int i = 0; i < q; ++i) {
    std::string driver, car;
    std::cin >> driver >> car;
    arr.push_back({driver, car});
    root = Splay(root, arr[i].first);
    root = Splay(root, arr[i].second);
  }
  /*size_t w;
  std::cin >> w;
  while (w != 0) {

    --q;
  }*/
  preOrder(root);
  return 0;
}
 