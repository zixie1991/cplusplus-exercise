#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

const int kMaxVertex = 10000;

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int** mat;
};

// 无向图

void DFS(DenseGraph& graph, int u, bool* visited) {
  for (int v = 0; v < graph.num_vertexes; v++) {
    if (graph.mat[u][v] && !visited[v]) {
      visited[v] = true;
      DFS(graph, v, visited);

      // TODO do something
    }
  }
}

// POJ Satellite Photographs
void DFS(DenseGraph& graph, int u, bool** visited) {
  for (int v = 0; v < graph.num_vertexes; v++) {
    if (graph.mat[u][v] && !visited[u][v]) {
      visited[u][v] = visited[v][u] = true;
      DFS(graph, v, visited);

      // TODO do something
    }
  }
}

int main() {
  int** a;
  int n = 10;
  int m = 5;
  a = new int*[n];
  for (int i = 0; i < n; i++) {
    a[i] = new int[m];
  }

  a[1][0] = 1;
  cout << a[1][0] << endl;
  int b[n][m];

  return 0;
}
