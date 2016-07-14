#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// 欧拉回路/欧拉通路
// POJ 1041

// 前向星
struct EdgeNode {
  int from;
  int to;
  int weight; // 权重，编号...
  int next;
};

struct ForwardStarGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int* head; // 顶点
  EdgeNode* edge;
};

// 无向图的连通性
bool IsConnected(ForwardStarGraph& graph) {
  bool* visited = new bool[graph.num_vertexes];
  for (int i = 0; i < graph.num_vertexes; i++) {
    visited[i] = false;
  }

  queue<int> q;
  visited[0] = true;
  q.push(0);
  int cnt = 0;
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    cnt++;

    for (int j = graph.head[i]; j != -1; j = graph.edge[j].next) {
      if (!visited[graph.edge[j].to]) {
        visited[graph.edge[j].to] = true;
        q.push(graph.edge[j].to);
      }
    }
  }

  return cnt == graph.num_vertexes;
}

// 无向图
bool IsEuler(ForwardStarGraph& graph) {
  // 顶点的度
  int* degree = new int[graph.num_vertexes];
  memset(degree, 0, sizeof(degree));
  for (int i = 0; i < graph.num_vertexes; i++) {
    for (int j = graph.head[i]; j != -1; j = graph.edge[j].next) {
      degree[i]++;
    }
  }

  int odd = 0;
  for (int i = 0; i < graph.num_vertexes; i++) {
    if (degree[i] & 1) {
      odd++;
    }
  }

  return (odd == 0 || odd == 2);
}

// 欧拉通路
void Euler(ForwardStarGraph& graph, int src, bool* visited, stack<int>* path) {
  for (int j = graph.head[src]; j != -1; j = graph.edge[j].next) {
    if (!visited[j]) {
      visited[j] = true;
      Euler(graph, graph.edge[j].to, visited, path);

      // 记录欧拉通路
      path->push(j);
    }
  }
}

int main() {
  return 0;
}
