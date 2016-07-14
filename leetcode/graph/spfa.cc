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

// Shortest Path Faster Algorithm, 时间: O(kE), 不稳定
bool SPFA(ForwardStarGraph& graph, int src, int* dist) {
  bool* in_queue = new bool[graph.num_vertexes]; // 顶点是否在队列中
  int* push_queue_count = new int[graph.num_vertexes]; // 顶点入队次数
  for (int i = 0; i < graph.num_vertexes; i++) {
    dist[i] = INT_MAX;
    in_queue[i] = false;
    push_queue_count[i] = 0;
  }

  dist[src] = 0;
  in_queue[src] = true;
  push_queue_count[src]++;
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
          push_queue_count[graph.edge[j].to]++;

          if (push_queue_count[graph.edge[j].to] == graph.num_vertexes) {
            return false; // 负权回路
          }
        }
      }
    }
  }

  return true;
}

int main() {
  return 0;
}
