#include <iostream>

struct Node {
  int data;
  Node* next;
};

class List {
 private:
  Node* head_;

 public:
  List();
  ~List();
  void PushBack(int value);
  void Pop(int value);
  bool Find(int value);
};

List::List() { head_ = nullptr; }

List::~List() {
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
}

void List::PushBack(int value) {
  if (!Find(value)) {
    Node* new_node = new Node();
    new_node->data = value;
    new_node->next = head_;
    head_ = new_node;
  }
}

void List::Pop(int value) {
  if (Find(value)) {
    if (head_ != nullptr && head_->data == value) {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
      return;
    }
    Node* current = head_;
    if (current == nullptr) {
      return;
    }
    while (current->next != nullptr && current->next->data != value) {
      current = current->next;
    }
    if (current->next != nullptr) {
      Node* temp = current->next;
      current->next = temp->next;
      delete temp;
    }
  }
}

bool List::Find(int value) {
  Node* current = head_;
  while (current != nullptr) {
    if (current->data == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

class Hashtable {
 private:
  List** arr_;
  int length_;

 public:
  Hashtable(int size);
  ~Hashtable();
  int HashFunc(int value);
  void Insert(int value);
  void Extract(int value);
  void Find(int value);
};

Hashtable::Hashtable(int size) {
  arr_ = new List*[size];
  for (int i = 0; i < size; i++) {
    arr_[i] = new List();
  }
  length_ = size;
}

Hashtable::~Hashtable() {
  for (int i = 0; i != length_; i++) {
    delete arr_[i];
  }
  delete[] arr_;
}

int Hashtable::HashFunc(int value) { return value % length_; }

void Hashtable::Insert(int value) {
  int position = HashFunc(value);
  List* lst = arr_[position];
  lst->PushBack(value);
}

void Hashtable::Extract(int value) {
  int position = HashFunc(value);
  List* lst = arr_[position];
  lst->Pop(value);
}

void Hashtable::Find(int value) {
  int position = HashFunc(value);
  List* lst = arr_[position];
  if (lst->Find(value)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
}

int main() {
  int test;
  std::cin >> test;
  Hashtable hash(test);
  while (test != 0) {
    std::string cmd;
    int value;
    std::cin >> cmd >> value;
    if (cmd == "+") {
      hash.Insert(value);
    }
    if (cmd == "-") {
      hash.Extract(value);
    }
    if (cmd == "?") {
      hash.Find(value);
    }
    --test;
  }
}
