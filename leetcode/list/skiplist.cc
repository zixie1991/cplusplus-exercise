#include "skiplist.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::map;

template <typename Key, typename Value>
SkipList<Key, Value>::SkipList():
  level_(0),
  size_(0),
  head_(NULL)
{
  NewList();
}

template <typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
  DeleteList();
}

template <typename Key, typename Value>
int SkipList<Key, Value>::Search(const Key& key, Value* value) {
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

template <typename Key, typename Value>
int SkipList<Key, Value>::Insert(const Key& key, const Value& value) {
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

  size_++;

  return 0;
}

template <typename Key, typename Value>
int SkipList<Key, Value>::Delete(const Key& key, Value* value) {
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
  size_--;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::Print() {
  cout << level_ << " level, " << size_ << " node skip list" << endl;
  for (int i = 0; i < level_; i++) {
    ListNodeType *ptr = head_;
    cout << "|->";
    while ((ptr = ptr->next[i])) {
      cout << ptr->key << "->";
    }
    cout << "NULL" << endl;
  }
}

template <typename Key, typename Value>
void SkipList<Key, Value>::NewList() {
  head_ = NewListNode(kMaxHeight);

  srand(time(0));
}

template <typename Key, typename Value>
void SkipList<Key, Value>::DeleteList() {
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

template <typename Key, typename Value>
ListNode<Key, Value>* SkipList<Key, Value>::NewListNode(int level, const Key& key, const Value& value) {
  ListNodeType *new_node = new ListNodeType(key, value);
  new_node->next = new ListNodeType*[level];

  for (int i = 0; i < level; i++) {
    new_node->next[i] = NULL;
  }

  return new_node;
}

template <typename Key, typename Value>
void SkipList<Key, Value>::DeleteListNode(ListNodeType *node) {
  if (!node) {
    return ;
  }

  delete[] node->next;
  delete node;
}

template <typename Key, typename Value>
int SkipList<Key, Value>::RandomLevel() {
  int level = 1;
  while (rand() % 2) {
    level++;
  }

  level = level > kMaxHeight ? kMaxHeight : level;
  return level;
}

template class SkipList<int, int>;
