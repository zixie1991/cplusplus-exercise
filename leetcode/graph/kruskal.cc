#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <algorithm>
#include <vector>

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

// 并查集
class DisjointSet {
  public:
    DisjointSet(int num_elements):
      elements(num_elements)
    {
      for (size_t x = 0; x < elements.size(); x++) {
        elements[x] = x;
      }
    }

    void Union(int x, int y) {
      int px = Find(x);
      int py = Find(y);

      elements[px] = py;
    }

    int Find(int x) {
      if (elements[x] == x) {
        return x;
      }

      return elements[x] = Find(elements[x]);
    }

  private:
    vector<int> elements; 
};


// 带权无向图, 稀疏图
// Kruskal算法, 时间: O(ElogE)
int Kruskal(ForwardStarGraph& graph) {
  int sum = 0;
  DisjointSet s(graph.num_vertexes);
  sort(graph.edge, graph.edge + graph.num_edges);

  int j = 0;
  for (int i = 0; i < graph.num_vertexes; i++) {
    while (j < graph.num_edges && s.Find(graph.edge[j].from) == 
       s.Find(graph.edge[j].to)) {
      j++;
    }

    if (j >= graph.num_edges) {
      // 不连通
      return -1;
    }

    s.Union(graph.edge[j].from, graph.edge[j].to);
    sum += graph.edge[j++].weight;
  }

  return sum;
}

int main() {
}
