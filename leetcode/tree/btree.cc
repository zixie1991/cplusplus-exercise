#include "btree.h"

#include <queue>
#include <iostream>

using std::upper_bound;
using std::lower_bound;
using std::queue;
using std::cout;
using std::endl;
using std::vector;

template <typename K, typename V>
BTree<K, V>::BTree(int rank):
  rank_(rank),
  size_(0),
  root_(NULL)
{
}

template <typename K, typename V>
int BTree<K, V>::Get(const K& key, V* value, BTreeNodeType **parent, BTreeNodeType **current) {
  int ret = -1;
  BTreeNodeType *ptr = root_;
  BTreeNodeType *prev = NULL;
  if (current) {
    *current = NULL;
  }

  while (ptr) {
    auto iter = lower_bound(ptr->keys.begin(), ptr->keys.end(), key);
    int key_idx = iter - ptr->keys.begin();

    // found it
    if (*iter == key) {
      if (value) {
        *value = ptr->values[key_idx];
      }
      if (current) {
        *current = ptr;
      }

      ret = 0;
      break ;
    }

    // next level
    prev = ptr;
    ptr = ptr->children[key_idx];
  }

  if (parent) {
    *parent = prev;
  }

  return ret;
}

template <typename K, typename V>
int BTree<K, V>::Put(const K& key, const V& value, bool overwrite) {
  BTreeNodeType *ptr = NULL;
  // 重复的关键字
  if (Get(key, NULL, &ptr) == 0) {
    return -1;
  }

  if (!ptr) {
    // 空树
    ptr = new BTreeNodeType();
    ptr->keys.push_back(key);
    ptr->values.push_back(value);
    ptr->children.push_back(NULL);
    ptr->children.push_back(NULL);
    root_ = ptr;
    size_++;

    return 0;
  }

  auto iter = upper_bound(ptr->keys.begin(), ptr->keys.end(), key);
  int key_idx = iter - ptr->keys.begin();
  ptr->keys.insert(ptr->keys.begin() + key_idx, key);
  ptr->values.insert(ptr->values.begin() + key_idx, value);
  ptr->children.push_back(NULL); // 叶子节点
  size_++;

  // 上溢出
  while (ptr && ptr->keys.size() >= rank_) {
    BTreeNodeType *tmp = ptr->parent;
    SolveOverflow(ptr);
    ptr = tmp;
  }

  return 0;
}

template <typename K, typename V>
int BTree<K, V>::Remove(const K& key, V* value) {
  BTreeNodeType *ptr = NULL;
  if (Get(key, value, NULL, &ptr) < 0) {
    // 查找失败
    return -1;
  }

  auto iter = lower_bound(ptr->keys.begin(), ptr->keys.end(), key);
  int key_idx = iter - ptr->keys.begin();

  if (ptr->children[0]) {
    BTreeNodeType *tmp = ptr;
    ptr = ptr->children[key_idx + 1];
    while (ptr->children[0]) {
      ptr = ptr->children[0];
    }
    tmp->keys[key_idx] = ptr->keys[0];
    tmp->values[key_idx] = ptr->values[0];
    key_idx = 0;
  }

  ptr->keys.erase(ptr->keys.begin() + key_idx);
  ptr->values.erase(ptr->values.begin() + key_idx);
  ptr->children.pop_back();
  size_--;

  // 下溢出
  while (ptr != root_ && ptr->keys.size() < (rank_ - 1) / 2) {
    BTreeNodeType *tmp = ptr->parent;
    SolveUnderflow(ptr);
    ptr = tmp;
  }

  if (ptr == root_ && root_->keys.empty()) {
    ptr = root_;
    root_ = root_->children[0];
    root_->parent = NULL;

    delete ptr;
  }

  return 0;
}

template <typename K, typename V>
void BTree<K, V>::SolveOverflow(BTreeNodeType *node) {
  int min_keys = (rank_ - 1) / 2;
  BTreeNodeType *parent = node->parent;

  // split left part
  BTreeNodeType *left = new BTreeNodeType();
  for (int i = 0; i < min_keys; i++) {
    left->keys.push_back(node->keys[i]);
    left->values.push_back(node->values[i]);
    left->children.push_back(node->children[i]);
  }
  left->children.push_back(node->children[min_keys]);
  for (int i = 0; i < left->children.size(); i++) {
    if (left->children[i]) {
      left->children[i]->parent = left;
    }
  }

  // split right part
  BTreeNodeType *right = new BTreeNodeType();
  for (int i = min_keys + 1; i < node->keys.size(); i++) {
    right->keys.push_back(node->keys[i]);
    right->values.push_back(node->values[i]);
    right->children.push_back(node->children[i]);
  }
  right->children.push_back(node->children[node->keys.size()]);
  for (int i = 0; i < right->children.size(); i++) {
    if (right->children[i]) {
      right->children[i]->parent = right;
    }
  }

  if (!parent) {
    // 根节点上溢出
    parent = new BTreeNodeType();
    root_ = parent;
  }

  left->parent = parent;
  right->parent = parent;
  auto iter = upper_bound(parent->keys.begin(), parent->keys.end(), node->keys[min_keys]);
  int key_idx = iter - parent->keys.begin();
  parent->keys.insert(parent->keys.begin() + key_idx, node->keys[min_keys]);
  parent->values.insert(parent->values.begin() + key_idx, node->values[min_keys]);
  if (!parent->children.empty()) {
    parent->children.erase(parent->children.begin() + key_idx);
  }
  parent->children.insert(parent->children.begin() + key_idx, right);
  parent->children.insert(parent->children.begin() + key_idx, left);

  delete node;
}

template <typename K, typename V>
void BTree<K, V>::SolveUnderflow(BTreeNodeType *node) {
  BTreeNodeType *parent = node->parent;
  int key_idx = 0;
  while (parent->children[key_idx] != node) {
    key_idx++;
  }
  int min_keys = (rank_ + 1) / 2;

  // borrow from left brother
  if (key_idx > 0 && parent->children[key_idx - 1]->keys.size() > min_keys) {
    BTreeNodeType *left = parent->children[key_idx - 1];

    node->keys.insert(node->keys.begin(), parent->keys[key_idx - 1]);
    node->values.insert(node->values.begin(), parent->values[key_idx - 1]);
    node->children.insert(node->children.begin(), left->children.back());
    left->children.pop_back();

    parent->keys[key_idx - 1] = left->keys.back();
    left->keys.pop_back();
    parent->values[key_idx - 1] = left->values.back();
    left->values.pop_back();

    return ;
  }

  // borrow from right brother
  if (key_idx < parent->children.size() - 1 && parent->children[key_idx + 1]->keys.size() > min_keys) {
    BTreeNodeType *right = parent->children[key_idx + 1];

    node->keys.push_back(parent->keys[key_idx]);
    node->values.push_back(parent->values[key_idx]);
    node->children.push_back(right->children.front());
    right->children.erase(right->children.begin());

    parent->keys[key_idx] = right->keys.front();
    right->keys.erase(right->keys.begin());
    parent->values[key_idx] = right->values.front();
    right->values.erase(right->values.begin());

    return ;
  }

  // merge with left brother
  if (key_idx > 0) {
    BTreeNodeType *left = parent->children[key_idx - 1];
    left->keys.push_back(parent->keys[key_idx - 1]);
    left->values.push_back(parent->values[key_idx - 1]);
    
    int update_idx = left->children.size();
    for (int i = 0; i < node->keys.size(); i++) {
      left->keys.push_back(node->keys[i]);
      left->values.push_back(node->values[i]);
      left->children.push_back(node->children[i]);
    }
    left->children.push_back(node->children[node->keys.size()]);
    for (int i = update_idx; i < left->children.size(); i++) {
      if (left->children[i]) {
        left->children[i]->parent = left;
      }
    }

    parent->keys.erase(parent->keys.begin() + key_idx - 1);
    parent->values.erase(parent->values.begin() + key_idx - 1);
    parent->children.erase(parent->children.begin() + key_idx);

    delete node;
    return ;
  }

  // merge with right brother
  BTreeNodeType *right = parent->children[key_idx + 1];

  node->keys.push_back(parent->keys[key_idx]);
  node->values.push_back(parent->values[key_idx]);

  int update_idx = node->children.size();
  for (int i = 0; i < right->keys.size(); i++) {
    node->keys.push_back(right->keys[i]);
    node->values.push_back(right->values[i]);
    node->children.push_back(right->children[i]);
  }
  node->children.push_back(right->children[right->keys.size()]);
  for (int i = update_idx; i < node->children.size(); i++) {
    node->children[i]->parent = node;
  }

  parent->keys.erase(parent->keys.begin() + key_idx);
  parent->values.erase(parent->values.begin() + key_idx);
  parent->children.erase(parent->children.begin() + key_idx + 1);

  delete right;
}

template <typename K, typename V>
void BTree<K, V>::Print() {
  cout << rank_ << " rank, " << size_ << " node B-tree" << endl;
  queue<BTreeNodeType*> q;
  if (!root_) {
    return ;
  }

  q.push(root_);
  int level_size = 1;
  queue<char> split_vec;
  split_vec.push('|');

  while (!q.empty()) {
    int n = 0;
    while (level_size--) {
      BTreeNodeType *ptr = q.front();
      q.pop();
      for (int i = 0; i < ptr->keys.size(); i++) {
        cout << ptr->keys[i] << " ";
      }
      cout << "#";
      char c = split_vec.front();
      split_vec.pop();
      if (c) {
        cout << c;
      }

      for (int i = 0; i < ptr->children.size(); i++) {
        if (ptr->children[i]) {
          q.push(ptr->children[i]);
          n++;
          if (i > 0) {
            split_vec.push(0);
          }
        }
      }
      split_vec.push('|');
    }
    level_size = n;
    cout << endl;
  }
}

template class BTree<int, int>;
