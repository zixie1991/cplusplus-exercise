#ifndef BTREE_H_
#define BTREE_H_

#include <vector>
#include <algorithm>


/**
 * @brief B树节点
 *
 * @tparam K 关键字类型
 * @tparam V 记录类型
 */
template <typename K, typename V>
struct BTreeNode {
  BTreeNode *parent; // 父节点
  std::vector<K> keys; // 关键字
  std::vector<V> values; // 记录
  std::vector<BTreeNode*> children; // 子节点

  BTreeNode(): 
    parent(NULL) 
  {
  }
};


/**
 * @brief B树
 *
 * @tparam K 关键字类型
 * @tparam V 记录类型
 */
template <typename K, typename V>
class BTree {
  public:
    typedef BTreeNode<K, V> BTreeNodeType;

    BTree(int rank);
    /**
     * @brief 查找
     *
     * @param key
     * @param value
     *
     * @return 
     */
    int Get(const K& key, V* value, BTreeNodeType **parent=NULL, BTreeNodeType **current=NULL);
    /**
     * @brief 插入
     *
     * @param key
     * @param value
     *
     * @return 
     */
    int Put(const K& key, const V& value, bool overwrite=false);
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
     * @brief 打印B树
     */
    void Print();

  private:
    /**
     * @brief 解决插入上溢出
     *
     * @param 
     */
    void SolveOverflow(BTreeNodeType *node);
    /**
     * @brief 解决删除下溢出
     *
     * @param 
     */
    void SolveUnderflow(BTreeNodeType *node);

    int rank_; // B树的阶
    int size_; // B树键值对的个数
    BTreeNodeType *root_; // B树根节点
};

#endif
