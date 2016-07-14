#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <iostream>
#include <algorithm>

using namespace std;

// 所有点对最短路径
// 最短路径算法——Dijkstra,Bellman-Ford,Floyd-Warshall,Johnson: http://dsqiu.iteye.com/blog/1689163

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int** mat;
};

// 带权有向图(无负权回路)
// Floyd算法, 时间: O(V**3)
void Floyd(DenseGraph& graph, int** dist) {
  for (int i = 0; i < graph.num_vertexes; i++) {
    for (int j = 0; j < graph.num_vertexes; j++) {
      dist[i][j] = graph.mat[i][j];
    }
  }

  for (int k = 0; k < graph.num_vertexes; k++) {
    for (int i = 0; i < graph.num_vertexes; i++) {
      for (int j = 0; j < graph.num_vertexes; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

int main() {
}
