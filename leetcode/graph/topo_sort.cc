#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 拓扑排序

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int** mat;
};

// 有向图(无权)
bool TopoSort(DenseGraph& graph, vector<int> topo_vec) {
  int* in_degree = new int[graph.num_vertexes]; // 顶点的入读

  memset(in_degree, 0, sizeof(in_degree));

  for (int from = 0; from < graph.num_vertexes; from++) {
    for (int to = 0; to < graph.num_vertexes; to++) {
      if (graph.mat[from][to]) {
        in_degree[to]++;
      }
    }
  } 

  queue<int> zero_in_degree_vertexes;
  for (int i = 0; i < graph.num_vertexes; i++) {
    if (!(in_degree[i] & 1)) {
      zero_in_degree_vertexes.push(i);
    }
  }

  while (zero_in_degree_vertexes.empty()) {
    int from = zero_in_degree_vertexes.front();
    zero_in_degree_vertexes.pop();

    topo_vec.push_back(from);
    for (int to = 0; to < graph.num_vertexes; to++) {
      if (graph.mat[from][to]) {
        in_degree[to]--;

        if (in_degree[to]) {
          zero_in_degree_vertexes.push(to);
        }
      }
    }
  }

  delete[] in_degree;

  return topo_vec.size() == graph.num_vertexes;
}

int main() {
}
