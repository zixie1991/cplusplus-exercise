#include "bplustree.h"

#include <algorithm>
#include <iostream>
#include <queue>

using std::lower_bound;
using std::upper_bound;
using std::vector;
using std::cout;
using std::endl;
using std::queue;

template <typename K, typename V>
BPlusTree<K, V>::BPlusTree(int rank):
  rank_(rank),
  size_(0),
  root_(NULL)
{
}

template <typename K, typename V>
int BPlusTree<K, V>::Get(const K& key, V* value, BPlusLeafNodeType **current) {
  int ret = -1;
  BPlusTreeNodeType *ptr = root_;
  BPlusTreeNodeType *prev = NULL;
  if (current) {
    *current = NULL;
  }

  while (ptr) {
    auto iter = lower_bound(ptr->keys.begin(), ptr->keys.end(), key);
    int key_idx = iter - ptr->keys.begin();
    if (key_idx >= ptr->keys.size()) {
      key_idx = ptr->keys.size() - 1;
    }

    if (ptr->children.empty()) {
      // 叶子节点
      BPlusLeafNodeType *leaf = dynamic_cast<BPlusLeafNodeType*>(ptr);

      if (current) {
        *current = leaf;
      }

      if (*iter == key) {
        if (value) {
          *value = leaf->values[key_idx];
        }
        ret = 0;
      }

      break;
    }

    prev = ptr;
    ptr = ptr->children[key_idx];
  }

  return ret;
}

template <typename K, typename V>
int BPlusTree<K, V>::RangeGet(const K& lkey, const K& rkey, std::vector<V> *values) {
  BPlusLeafNodeType *lnode = NULL;
  Get(lkey, NULL, &lnode);
  BPlusLeafNodeType *rnode = NULL;
  Get(rkey, NULL, &rnode);

  BPlusLeafNodeType *ptr = lnode;
  while (ptr) {
    for (int i = 0; i < ptr->keys.size(); i++) {
      if (ptr->keys[i] > rkey) {
        break;
      }
      (*values).push_back(ptr->values[i]);
    }

    if (ptr == rnode) {
      break;
    }

    ptr = ptr->next;
  }

  return 0;
}

template <typename K, typename V>
int BPlusTree<K, V>::Put(const K& key, const V& value) {
  BPlusLeafNodeType *current = NULL;
  if(Get(key, NULL, &current) == 0) {
    // 重复关键字
    return -1;
  }

  if (!current) {
    // 空B+树
    current = new BPlusLeafNodeType();
    current->keys.push_back(key);
    current->values.push_back(value);
    root_ = current;
    size_++;

    return 0;
  }

  auto iter = upper_bound(current->keys.begin(), current->keys.end(), key);
  int key_idx = iter - current->keys.begin();
  current->keys.insert(current->keys.begin() + key_idx, key);
  current->values.insert(current->values.begin() + key_idx, value);
  size_++;

  // 上溢出
  BPlusTreeNodeType *ptr = dynamic_cast<BPlusTreeNodeType*>(current);
  while (ptr && ptr->keys.size() > rank_) {
    BPlusTreeNodeType *tmp = ptr->parent;
    SolveOverflow(ptr);
    ptr = tmp;
  }

  while (ptr && ptr->parent) {
    BPlusTreeNodeType *parent = ptr->parent;
    auto iter = lower_bound(parent->keys.begin(), parent->keys.end(), ptr->keys.back());
    if (iter != parent->keys.end() && *iter == ptr->keys.back()) {
      break;
    }

    key_idx = iter - parent->keys.begin();
    if (key_idx >= parent->keys.size()) {
      key_idx = parent->keys.size() - 1;
    }
    parent->keys[key_idx] = ptr->keys.back();
    ptr = parent;
  }

  return 0;
}

template <typename K, typename V>
int BPlusTree<K, V>::Remove(const K& key, V* value) {
  BPlusLeafNodeType *current = NULL;
  if (Get(key, value, &current) < 0) {
    // 查找关键字失败
    return -1;
  }

  auto iter = lower_bound(current->keys.begin(), current->keys.end(), key);
  int key_idx = iter - current->keys.begin();
  current->keys.erase(current->keys.begin() + key_idx);
  current->values.erase(current->values.begin() + key_idx);
  size_--;

  BPlusTreeNodeType *ptr = static_cast<BPlusTreeNodeType*>(current);
  while (ptr != root_ && ptr->keys.size() < (rank_ + 1) / 2) {
    BPlusTreeNodeType *tmp = ptr->parent;
    SolveUnderflow(ptr);
    ptr = tmp;
  }

  if (ptr == root_ && root_->keys.empty()) {
    delete root_;
    root_ = NULL;

    return 0;
  }

  while (ptr && ptr->parent) {
    BPlusTreeNodeType *parent = ptr->parent;
    auto iter = lower_bound(parent->keys.begin(), parent->keys.end(), ptr->keys.back());
    if (iter != parent->keys.end() && *iter == ptr->keys.back()) {
      break;
    }

    key_idx = iter - parent->keys.begin();
    if (key_idx >= parent->keys.size()) {
      key_idx = parent->keys.size() - 1;
    }
    parent->keys[key_idx] = ptr->keys.back();
    ptr = parent;
  }

  return 0;
}

template <typename K, typename V>
void BPlusTree<K, V>::SolveOverflow(BPlusTreeNodeType *node) {
  BPlusTreeNodeType *parent = node->parent;
  int min_keys = (rank_ + 1) / 2;

  // split right part
  BPlusTreeNodeType *right = NULL;
  if (node->children.empty()) {
    BPlusLeafNodeType *right_leaf = new BPlusLeafNodeType();
    BPlusLeafNodeType *leaf = dynamic_cast<BPlusLeafNodeType*>(node);

    for (int i = min_keys; i < leaf->keys.size(); i++) {
      right_leaf->keys.push_back(leaf->keys[i]);
      right_leaf->values.push_back(leaf->values[i]);
    }

    right = static_cast<BPlusTreeNodeType*>(right_leaf);
  } else {
    BPlusTreeNodeType *right_node = new BPlusTreeNodeType();

    for (int i = min_keys; i < node->keys.size(); i++) {
      right_node->keys.push_back(node->keys[i]);
      right_node->children.push_back(node->children[i]);
    }

    for (int i = 0; i < right_node->children.size(); i++) {
      right_node->children[i]->parent = right_node;
    }

    right = right_node;
  }

  // split left part
  BPlusTreeNodeType *left = NULL;
  if (node->children.empty()) {
    BPlusLeafNodeType *left_leaf = dynamic_cast<BPlusLeafNodeType*>(node);

    while (left_leaf->keys.size() > min_keys) {
      left_leaf->keys.pop_back();
      left_leaf->values.pop_back();
    }

    left = static_cast<BPlusTreeNodeType*>(left_leaf);
  } else {
    BPlusTreeNodeType *left_node = node;

    while (left_node->keys.size() > min_keys) {
      left_node->keys.pop_back();
      left_node->children.pop_back();
    }

    left = left_node;
  }

  int key_idx = 0;
  // 根节点上溢出
  if (!parent) {
    parent = new BPlusTreeNodeType();
    root_ = parent;
  } else {
    auto iter = lower_bound(parent->keys.begin(), parent->keys.end(), right->keys.back());
    key_idx = iter - parent->keys.begin();
    if (key_idx >= parent->keys.size()) {
      key_idx = parent->keys.size() - 1;
    }
    parent->keys.erase(parent->keys.begin() + key_idx);
    parent->children.erase(parent->children.begin() + key_idx);
  }

  if (node->children.empty()) {
    BPlusLeafNodeType *left_leaf = dynamic_cast<BPlusLeafNodeType*>(left);
    BPlusLeafNodeType *right_leaf = dynamic_cast<BPlusLeafNodeType*>(right);
    BPlusLeafNodeType *tmp = left_leaf->next;
    left_leaf->next = right_leaf;
    right_leaf->next = tmp;
  }

  left->parent = parent;
  right->parent = parent;
  parent->keys.insert(parent->keys.begin() + key_idx, right->keys.back());
  parent->keys.insert(parent->keys.begin() + key_idx, left->keys.back());
  parent->children.insert(parent->children.begin() + key_idx, right);
  parent->children.insert(parent->children.begin() + key_idx, left);
}

template <typename K, typename V>
void BPlusTree<K, V>::SolveUnderflow(BPlusTreeNodeType *node) {
  int min_keys = (rank_ + 1) / 2;
  BPlusTreeNodeType *parent = node->parent;
  auto iter = lower_bound(parent->keys.begin(), parent->keys.end(), node->keys.back());
  int key_idx = iter - parent->keys.begin();

  // borrow from left brother
  if (key_idx > 0 && parent->children[key_idx - 1]->keys.size() > min_keys) {
    if (node->children.empty()) {
      // 叶子节点
      BPlusLeafNodeType *left_leaf = dynamic_cast<BPlusLeafNodeType*>(parent->children[key_idx - 1]);
      BPlusLeafNodeType *leaf = dynamic_cast<BPlusLeafNodeType*>(node);

      leaf->keys.insert(leaf->keys.begin(), left_leaf->keys.back());
      left_leaf->keys.pop_back();
      leaf->values.insert(leaf->values.begin(), left_leaf->values.back());
      left_leaf->values.pop_back();

      parent->keys[key_idx - 1] = left_leaf->keys.back();
      parent->keys[key_idx] = leaf->keys.back();

    } else {
      BPlusTreeNodeType *left_node = parent->children[key_idx - 1];

      node->keys.insert(node->keys.begin(), left_node->keys.back());
      left_node->keys.pop_back();
      node->children.insert(node->children.begin(), left_node->children.back());
      left_node->children.pop_back();
      node->children.back()->parent = node;
      
      parent->keys[key_idx - 1] = left_node->keys.back();
      parent->keys[key_idx] = node->keys.back();
    }

    return ;
  }

  // borrow from right brother
  if (key_idx < parent->keys.size() - 1 && parent->children[key_idx + 1]->keys.size() > min_keys) {
    if (node->children.empty()) {
      // 叶子节点
      BPlusLeafNodeType *right_leaf = dynamic_cast<BPlusLeafNodeType*>(parent->children[key_idx + 1]);
      BPlusLeafNodeType *leaf = dynamic_cast<BPlusLeafNodeType*>(node);

      leaf->keys.push_back(right_leaf->keys.front());
      right_leaf->keys.erase(right_leaf->keys.begin());
      leaf->values.push_back(right_leaf->values.front());
      right_leaf->values.erase(right_leaf->values.begin());

      parent->keys[key_idx] = leaf->keys.back();
      parent->keys[key_idx + 1] = right_leaf->keys.back();

    } else {
      BPlusTreeNodeType *right_node = parent->children[key_idx + 1];

      node->keys.push_back(right_node->keys.front());
      right_node->keys.erase(right_node->keys.begin());
      node->children.push_back(right_node->children.front());
      right_node->children.erase(right_node->children.begin());
      node->children.back()->parent = node;

      parent->keys[key_idx] = node->keys.back();
      parent->keys[key_idx + 1] = right_node->keys.back();
    }

    return ;
  }

  // merge with left brother
  if (key_idx > 0) {
    if (node->children.empty()) {
      // 叶子节点
      BPlusLeafNodeType *left_leaf = dynamic_cast<BPlusLeafNodeType*>(parent->children[key_idx - 1]);
      BPlusLeafNodeType *leaf = dynamic_cast<BPlusLeafNodeType*>(node);

      for (int i = 0; i < leaf->keys.size(); i++) {
        left_leaf->keys.push_back(leaf->keys[i]);
        left_leaf->values.push_back(leaf->values[i]);
      }

      parent->keys[key_idx - 1] = left_leaf->keys.back();
      parent->keys.erase(parent->keys.begin() + key_idx);
      parent->children.erase(parent->children.begin() + key_idx);

      left_leaf->next = leaf->next;

      delete leaf;
    } else {
      BPlusTreeNodeType *left_node = parent->children[key_idx - 1];

      for (int i = 0; i < node->keys.size(); i++) {
        left_node->keys.push_back(node->keys[i]);
        left_node->children.push_back(node->children[i]);
      }

      for (int i = 0; i < left_node->children.size(); i++) {
        left_node->children[i]->parent = left_node;
      }

      parent->keys[key_idx - 1] = left_node->keys.back();
      parent->keys.erase(parent->keys.begin() + key_idx);
      parent->children.erase(parent->children.begin() + key_idx);

      delete node;
    }

    return ;
  }

  // merge with right brother
  if (node->children.empty()) {
    // 叶子节点
    BPlusLeafNodeType *right_leaf = dynamic_cast<BPlusLeafNodeType*>(parent->children[key_idx + 1]);
    BPlusLeafNodeType *leaf = dynamic_cast<BPlusLeafNodeType*>(node);

    for (int i = 0; i < right_leaf->keys.size(); i++) {
      leaf->keys.push_back(right_leaf->keys[i]);
      leaf->values.push_back(right_leaf->values[i]);
    }

    parent->keys[key_idx] = leaf->keys.back();
    parent->keys.erase(parent->keys.begin() + key_idx + 1);
    parent->children.erase(parent->children.begin() + key_idx + 1);

    leaf->next = right_leaf->next;

    delete right_leaf;
  } else {
    BPlusTreeNodeType *right_node = parent->children[key_idx + 1];

    for (int i = 0; i < right_node->keys.size(); i++) {
      node->keys.push_back(right_node->keys[i]);
      node->children.push_back(right_node->children[i]);
    }

    for (int i = 0; i < node->children.size(); i++) {
      node->children[i]->parent = node;
    }

    parent->keys[key_idx] = node->keys.back();
    parent->keys.erase(parent->keys.begin() + key_idx + 1);
    parent->children.erase(parent->children.begin() + key_idx + 1);

    delete right_node;
  }
}

template <typename K, typename V>
void BPlusTree<K, V>::Print() {
  cout << rank_ << " rank, " << size_ << " node B+-tree" << endl;
  queue<BPlusTreeNodeType*> q;
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
      BPlusTreeNodeType *ptr = q.front();
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

template class BPlusTree<int, int>;
