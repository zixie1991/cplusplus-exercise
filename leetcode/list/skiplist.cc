#include "skiplist.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::map;

template <typename K, typename V>
SkipList<K, V>::SkipList():
  level_(0),
  head_(NULL)
{
  Init();
}

template <typename K, typename V>
SkipList<K, V>::~SkipList() {
  if (!head_) {
    return ;
  }

  ListNodeType *current = head_;
  ListNodeType *next = NULL;

  while (current) {
    next = current->next[0];
    DeleteListNode(current);
    current = next;
  }
}

template <typename K, typename V>
int SkipList<K, V>::Search(const K& key, V* value) {
  ListNodeType *current = head_;
  ListNodeType *next = NULL;
  for (int i = level_ - 1; i >= 0; i--) {
    while ((next = current->next[i]) && next->key < key) {
      current = next;
    }

    if (current->key == key) {
      *value = current->value;
      return 0;
    }
  }

  return -1;
}

template <typename K, typename V>
int SkipList<K, V>::Insert(const K& key, const V& value) {
  // 查找待插入的位置
  ListNodeType *update[kMaxHeight];
  ListNodeType *current = head_;
  ListNodeType *next = NULL;
  for (int i = level_ - 1; i >= 0; i--) {
    while ((next = current->next[i]) && next->key < key) {
      current = next;
    }

    update[i] = current;
  }

  if (current && current->key == key) {
    // 重复关键字
    current->value = value; // 覆盖记录
    return 0;
  }

  // 随机生成插入的层数
  int level = RandomLevel();

  // 更新level
  if (level > level_) {
    // 更新update
    for (int i = level_; i < level; i++) {
      update[i] = head_;
    }

    level_ = level;
  }

  // 从高层往底层插入
  ListNodeType *new_node = NewListNode(level, key, value);
  for (int i = level - 1; i >= 0; i--) {
    new_node->next[i] = update[i]->next[i];
    update[i]->next[i] = new_node;
  }

  return 0;
}

template <typename K, typename V>
int SkipList<K, V>::Erase(const K& key, V* value) {
  // 查找
  ListNodeType *update[kMaxHeight];
  ListNodeType *current = head_;
  ListNodeType *next = NULL;
  for (int i = level_ - 1; i >= 0; i--) {
    while ((next = current->next[i]) && next->key < key) {
      current = next;
    }

    update[i] = current;
  }

  if (!current || current->key < key) {
    // 查找失败
    return -1;
  }

  // 逐层删除
  for (int i = level_ - 1; i >= 0; i--) {
    if (update[i]->next[i] == current) {
      update[i]->next[i] = current->next[i];
      // 更新层数
      if (!head_->next[i]) {
        level_--;
      }
    }
  }

  DeleteListNode(current);
  current = NULL;
}

template <typename K, typename V>
void SkipList<K, V>::Print() {
  cout << level_ << " level skip list" << endl;
  for (int i = 0; i < level_; i++) {
    ListNodeType *ptr = head_;
    cout << "|->";
    while ((ptr = ptr->next[i])) {
      cout << ptr->key << "->";
    }
    cout << "NULL" << endl;
  }
}

template <typename K, typename V>
void SkipList<K, V>::Init() {
  head_ = NewListNode(kMaxHeight);

  srand(time(0));
}

template <typename K, typename V>
ListNode<K, V>* SkipList<K, V>::NewListNode(int level, const K& key, const V& value) {
  ListNodeType *new_node = new ListNodeType(key, value);
  new_node->next = new ListNodeType*[level];

  for (int i = 0; i < level; i++) {
    new_node->next[i] = NULL;
  }

  return new_node;
}

template <typename K, typename V>
void SkipList<K, V>::DeleteListNode(ListNodeType *node) {
  if (!node) {
    return ;
  }

  delete[] node->next;
  delete node;
}

template <typename K, typename V>
int SkipList<K, V>::RandomLevel() {
  int level = 1;
  while (rand() % 2) {
    level++;
  }

  level = level > kMaxHeight ? kMaxHeight : level;
  return level;
}

template class SkipList<int, int>;
