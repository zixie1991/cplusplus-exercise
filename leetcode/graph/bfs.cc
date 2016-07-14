#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <queue>

using namespace std;

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数
  int num_edges; // 边数
  int** mat;
};

// 无权图
void BFS(DenseGraph& graph) {
  bool* visited = new bool[graph.num_vertexes];
  queue<int> q;
  for (int i = 0; i < graph.num_vertexes; i++) {
    visited[i] = false;
  }

  visited[0] = true;
  q.push(0);
  while (!q.empty()) {
    int i = q.front();
    q.pop();

    // TODO do something

    for (int j = 0; j < graph.num_vertexes; j++) {
      if (graph.mat[i][j] && !visited[j]) {
        visited[j] = true;
        q.push(j);
      }
    }
  }

  delete[] visited;
}

void BFS2(DenseGraph& graph) {
  bool** visited = new bool*[graph.num_vertexes];
  queue<int> q;
  for (int i = 0; i < graph.num_vertexes; i++) {
    visited[i] = new bool[graph.num_vertexes];
  }

  for (int i = 0; i < graph.num_vertexes; i++) {
    for (int j = 0; j < graph.num_vertexes; j++) {
      visited[i][j] = false;
    }
  }

  q.push(0);
  while (!q.empty()) {
    int i = q.front();
    q.pop();

    for (int j = 0; j < graph.num_vertexes; j++) {
      if (graph.mat[i][j] && !visited[i][j]) {
        visited[i][j] = true;
        q.push(j);

        // TODO do something
      }
    }
  }

  for (int i = 0; i < graph.num_vertexes; i++) {
    delete[] visited[i];
  }
  delete[] visited;
}



int main() {
}
