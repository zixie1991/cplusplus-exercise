#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <iostream>

using namespace std;

// 单源最短路径

// 前向星
struct EdgeNode {
  int from;
  int to;
  int weight;
  int next;

  bool operator<(const EdgeNode& node) {
    return weight > node.weight;
  }

  EdgeNode(int u, int v, int w): from(u), to(v), weight(w) {}
};

struct ForwardStarGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int* head;
  EdgeNode* edge;
};

// Bellman-Ford算法, 时间O(VE)
bool BellmanFord(ForwardStarGraph& graph, int src, int* dist) {
  for (int i = 0; i < graph.num_vertexes; i++) {
    dist[i] = INT_MAX;
  }

  dist[0] = 0;
  for (int i = 0; i < graph.num_vertexes - 1; i++) {
    for (int j = 0; j < graph.num_edges; j++) {
      if (dist[graph.edge[j].from] + graph.edge[j].weight < dist[graph.edge[j].to]) {
        dist[graph.edge[j].to] = dist[graph.edge[j].from] + graph.edge[j].weight;
      }
    }
  }

  for (int i = 0; i < graph.num_edges; i++) {
    if (dist[graph.edge[i].from] + graph.edge[i].weight < dist[graph.edge[i].to]) {
      return false; // 负权回路
    }
  }

  return true;
}

int main() {
  return 0;
}
