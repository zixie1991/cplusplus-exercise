#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <stdio.h>

/**
 * @brief 链表节点
 *
 * @tparam K
 * @tparam V
 */
template <typename K, typename V>
struct ListNode {
  K key; // 关键字
  V value; // 记录
  ListNode **next; // 柔性数组, 实现结构体变长

  ListNode(): next(NULL) {}
  ListNode(const K& k, const V& v): key(k), value(v), next(NULL) {}
};

/**
 * @brief 跳表节点
 *
 * @tparam K
 * @tparam V
 */
template <typename K, typename V>
class SkipList {
  public:
    typedef ListNode<K, V> ListNodeType;

    SkipList();
    ~SkipList();

    int Search(const K& key, V* value);
    int Insert(const K& key, const V& value);
    int Erase(const K& key, V* value=NULL);

    /**
     * @brief 打印
     */
    void Print();

  private:
    /**
     * @brief 初始化
     */
    void Init();

    /**
     * @brief 创建节点
     *
     * @param level 层数
     * @param key 关键字
     * @param value 记录
     *
     * @return 
     */
    ListNodeType* NewListNode(int level, const K& key=0, const V& value=0);

    /**
     * @brief 删除节点
     *
     * @param node
     */
    void DeleteListNode(ListNodeType *node);

    /**
     * @brief 插入元素的层数生成的随机算法
     *
     * @return 
     */
    int RandomLevel();

    enum{kMaxHeight=12}; // 最大层数
    int level_; // 层数
    ListNodeType *head_; // 链表头节点
};

#endif
