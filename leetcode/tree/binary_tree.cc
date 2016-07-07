#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode(): val(0), left(NULL), right(NULL) {}
};

void TreeConstructWithPreOrderAndInOrder(int* pre_order, int* in_order, int n, TreeNode** tree) {
  if (n <= 0) {
    return ;
  }

  // malloc 只分配内存空间, 并未调用构造函数(被坑了)
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
  node->val = pre_order[0];
  node->left = NULL;
  node->right = NULL;
  *tree = node;

  int i = 0;
  for (; i < n; i++) {
    if (in_order[i] == pre_order[0]) {
      break;
    }
  }

  TreeConstructWithPreOrderAndInOrder(pre_order + 1, in_order, i, &(*tree)->left);
  TreeConstructWithPreOrderAndInOrder(pre_order + i + 1, in_order + i + 1, n - i - 1, &(*tree)->right);
}

void TreeDestroy(TreeNode** tree) {
  if (NULL == *tree) {
    return ;
  }

  TreeDestroy(&(*tree)->left);
  TreeDestroy(&(*tree)->right);

  free(*tree);
  *tree = NULL;
}

void TreePrintFromTopToBottom(TreeNode* tree) {
  queue<TreeNode*> q;

  if (NULL == tree) { 
    return ;
  }

  q.push(tree);
  cout << q.size() << endl;
  cout << tree->val << endl;

  while (!q.empty()) {
    TreeNode* node = q.front();
    q.pop();

    // print
    cout << node->val << " ";
    
    if (node->left) {
      q.push(node->left);
    }

    if (node->right) {
      q.push(node->right);
    }
  }
  cout << endl;
}

void TreePrintPreOrder(TreeNode* tree) {
  if (!tree) {
    return ;
  }
  cout << tree->val << " ";

  TreePrintPreOrder(tree->left);
  TreePrintPreOrder(tree->right);
}

// 二叉树镜像
void TreeMirror(TreeNode* tree) {
  if (!tree) {
    return ;
  }

  swap(tree->left, tree->right);

  if (tree->left) {
    TreeMirror(tree->left);
  }

  if (tree->right) {
    TreeMirror(tree->right);
  }
}

void TestTreeConstructWithPreOrderAndInOrder() {
  int pre_order[] = {1, 2, 4, 7, 3, 5, 6, 8};
  int in_order[] = {4, 7, 2, 1, 5, 3, 8, 6};
  int n = 8;
  TreeNode* tree = NULL;

  TreeConstructWithPreOrderAndInOrder(pre_order, in_order, n, &tree);
  TreePrintFromTopToBottom(tree);

  TreeDestroy(&tree);
}

void TestTreeMirror() {
  int pre_order[] = {1, 2, 4, 7, 3, 5, 6, 8};
  int in_order[] = {4, 7, 2, 1, 5, 3, 8, 6};
  int n = 8;
  TreeNode* tree = NULL;

  TreeConstructWithPreOrderAndInOrder(pre_order, in_order, n, &tree);
  TreePrintFromTopToBottom(tree);

  TreeMirror(tree);
  TreePrintFromTopToBottom(tree);
  TreeDestroy(&tree);
}

int main() {
  cout << "TestTreeConstructWithPreOrderAndInOrder:" << endl;
  TestTreeConstructWithPreOrderAndInOrder();
  cout << "TestTreeMirror:" << endl;
  TestTreeMirror();
  return 0;
}
