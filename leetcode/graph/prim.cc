#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <iostream>

using namespace std;

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int** mat;
};

// 带权无向图, 稠密图
// Prim算法, 时间: O(V**2)
int Prim(DenseGraph& graph) {
  bool* visited = new bool[graph.num_vertexes]; // 顶点是否在生成树中
  int* lowest = new int[graph.num_vertexes]; // 生成树外顶点i与生成树相连的最小边长
  int sum = 0;
  for (int i = 0; i < graph.num_vertexes; i++) {
    visited[i] = false;
    lowest[i] = graph.mat[0][i];
  }

  visited[0] = true;
  for (int i = 1; i < graph.num_vertexes; i++) {
    int min_dist = INT_MAX;
    int min_idx = -1;
    for (int j = 0; j < graph.num_vertexes; j++) {
      if (!visited[j] && lowest[j] < min_dist) {
        min_idx = j;
        min_dist = lowest[j];
      }
    }

    if (min_dist == INT_MAX) {
      // 图不连通
      return -1;
    }

    sum += lowest[min_idx];
    visited[min_idx] = true;

    for (int j = 0; j < graph.num_vertexes; j++) {
      if (!visited[j] && graph.mat[min_idx][j] < lowest[j]) {
        lowest[j] = graph.mat[min_idx][j];
      }
    }
  }

  return sum;
}

int main() {
  return 0;
}
