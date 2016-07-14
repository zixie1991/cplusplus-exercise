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

  bool operator<(const EdgeNode& node) const {
    return weight > node.weight;
  }

  EdgeNode(int u, int v, int w): from(u), to(v), weight(w) {}
};

struct ForwardStarGraph {
  int num_vertexes; // 顶点数
  int num_edges; // 边数
  int* head;
  EdgeNode* edge;
};

void AddEdge(int u, int v, int w, ForwardStarGraph* graph) {
  graph->edge[graph->num_edges].from = u;
  graph->edge[graph->num_edges].to = v;
  graph->edge[graph->num_edges].weight = w;
  graph->edge[graph->num_edges].next = graph->head[u];
  graph->head[u] = graph->num_edges++;
}

// 带权有向图(无负的权值)
// Dijkstra算法, 时间: O(ElogV)
void Dijkstra(ForwardStarGraph& graph, int src, int* dist) {
  bool* visited = new bool[graph.num_vertexes];
  priority_queue<EdgeNode> q;
  for (int i = 0; i < graph.num_vertexes; i++) {
    dist[i] = INT_MAX;
    visited[i] = false;
  }
  dist[src] = 0;
  visited[src] = true;
  q.push(EdgeNode(src, src, 0));
  for (int i = 0; i < graph.num_vertexes - 1; i++) {
    int from = q.top().to;
    for (int j = graph.head[from]; j != -1; j = graph.edge[j].next) {
      if (!visited[graph.edge[j].to] && 
          dist[from] + graph.edge[j].weight < dist[graph.edge[j].to]) {
        dist[graph.edge[j].to] = dist[from] + graph.edge[j].weight;
        q.push(EdgeNode(src, graph.edge[j].to, dist[graph.edge[j].to]));
      }
    }

    while (!q.empty() && visited[q.top().to]) {
      q.pop();
    }

    if (q.empty()) {
      break;
    }

    visited[q.top().to] = true;
  }
}

int main() {
}
