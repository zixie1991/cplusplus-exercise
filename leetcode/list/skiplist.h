#ifndef SKeyIPLIST_H_
#define SKeyIPLIST_H_

#include <stdio.h>

/**
 * @brief 链表节点
 *
 * @tparam Key 关键字类型
 * @tparam Value 记录类型
 */
template <typename Key, typename Value>
struct ListNode {
  Key key; // 关键字
  Value value; // 记录
  ListNode **next; // 柔性数组, 实现结构体变长

  ListNode(): next(NULL) {}
  ListNode(const Key& k, const Value& v): key(k), value(v), next(NULL) {}
};

/**
 * @brief 跳表节点
 *
 * @tparam Key 关键字类型
 * @tparam Value 记录类型
 */
template <typename Key, typename Value>
class SkipList {
  public:
    typedef ListNode<Key, Value> ListNodeType;

    SkipList();
    ~SkipList();

    /**
     * @brief 查找
     *
     * @param key 关键字
     * @param value 记录
     *
     * @return 
     */
    int Search(const Key& key, Value* value);

    /**
     * @brief 插入
     *
     * @param key 关键字
     * @param value 记录
     *
     * @return 
     */
    int Insert(const Key& key, const Value& value);

    /**
     * @brief 删除
     *
     * @param key 关键字
     * @param value 记录(可选)
     *
     * @return 
     */
    int Delete(const Key& key, Value* value=NULL);

    int level() const {
      return level_;
    }

    int size() const {
      return size_;
    }

    /**
     * @brief 打印
     */
    void Print();

  private:
    /**
     * @brief 初始化表
     */
    void NewList();

    /**
     * @brief 释放表
     */
    void DeleteList();

    /**
     * @brief 创建节点
     *
     * @param level 层数
     * @param key 关键字
     * @param value 记录
     *
     * @return 
     */
    ListNodeType* NewListNode(int level, const Key& key=0, const Value& value=0);

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
    int size_; // 节点数目
    ListNodeType *head_; // 链表头节点
};

#endif
