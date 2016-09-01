#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <stdio.h>

#include <vector>

/**
 * @brief B+树节点
 *
 * @tparam K 关键字类型
 */
template <typename K>
struct BPlusTreeNode {
  BPlusTreeNode *parent;
  std::vector<K> keys; // 关键字
  std::vector<BPlusTreeNode*> children; // 子节点

  BPlusTreeNode(): parent(NULL) {}
  virtual ~BPlusTreeNode() {}
};

/**
 * @brief B+树叶子节点
 *
 * @tparam K 关键字类型
 * @tparam V 记录类型
 */
template <typename K, typename V>
struct BPlusLeafNode: public BPlusTreeNode<K> {
  std::vector<V> values;
  BPlusLeafNode *next;

  BPlusLeafNode(): next(NULL) {}
};

/**
 * @brief B+树
 *
 * @tparam K 关键字类型
 * @tparam V 记录类型
 */
template <typename K, typename V>
class BPlusTree {
  public:
    typedef BPlusTreeNode<K> BPlusTreeNodeType;
    typedef BPlusLeafNode<K, V> BPlusLeafNodeType;

    BPlusTree(int rank);

    /**
     * @brief 关键字查找
     *
     * @param key 关键字
     * @param value 记录
     *
     * @return 
     */
    int Get(const K& key, V* value, BPlusLeafNodeType **current=NULL);
    /**
     * @brief 关键字范围查找
     *
     * @param lkey 关键字最小值
     * @param rkey 关键之最大值
     * @param values 记录结果
     *
     * @return 
     */
    int RangeGet(const K& lkey, const K& rkey, std::vector<V> *values);
    /**
     * @brief 插入
     *
     * @param key
     * @param value
     *
     * @return 
     */
    int Put(const K& key, const V& value);
    /**
     * @brief 删除
     *
     * @param key
     * @param value
     *
     * @return 
     */
    int Remove(const K& key, V* value=NULL);

    /**
     * @brief 打印B+树
     */
    void Print();

  private:
    /**
     * @brief 解决上溢出
     *
     * @param node
     */
    void SolveOverflow(BPlusTreeNodeType *node);
    /**
     * @brief 解决下溢出
     *
     * @param node
     */
    void SolveUnderflow(BPlusTreeNodeType *node);

    int rank_; // B+树的阶
    int size_; // B+树的键值对数目
    BPlusTreeNodeType *root_; // B+树根节点
};

#endif
