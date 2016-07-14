#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

// 前向星
struct EdgeNode {
  int from;
  int to;
  int weight;
  int next;

  bool operator<(const EdgeNode& node) {
    return weight < node.weight;
  }
};

struct ForwardStarGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int* head;
  EdgeNode* edge;
};

// 带权无向图
int Kruskal(ForwardStarGraph& graph) {
  int sum = 0;
  // 可以尝试并查集
  set<int> s;
  sort(graph.edge, graph.edge + graph.num_edges);

  int j = 0;
  for (int i = 0; i < graph.num_vertexes; i++) {
    while (j < graph.num_edges && s.count(graph.edge[j].from) && 
       s.count(graph.edge[j].to)) {
      j++;
    }

    if (j >= graph.num_edges) {
      return -1;
    }

    s.insert(j);
    sum += graph.edge[j++].weight;
  }

  return sum;
}

int main() {
}
