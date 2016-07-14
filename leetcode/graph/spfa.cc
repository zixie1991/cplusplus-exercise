#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <iostream>
#include <queue>

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

void SPFA(ForwardStarGraph& graph, int src, int* dist) {
  bool* in_queue = new bool[graph.num_vertexes]; // 是否在队列中
  for (int i = 0; i < graph.num_vertexes; i++) {
    dist[i] = INT_MAX;
    in_queue[i] = false;
  }

  dist[src] = 0;
  in_queue[src] = true;
  queue<int> q;
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    in_queue[i] = false;
    for (int j = graph.head[i]; j != -1; j = graph.edge[j].next) {
      if (dist[graph.edge[j].from] + graph.edge[j].weight < dist[graph.edge[j].to]) {
        dist[graph.edge[j].to] = dist[graph.edge[j].from] + graph.edge[j].weight;
        if (!in_queue[graph.edge[j].to]) {
          q.push(graph.edge[j].to);
          in_queue[graph.edge[j].to] = true;
        }
      }
    }
  }
}

int main() {
  return 0;
}
