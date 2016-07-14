const int kMaxVertex = 10000;
const int kMaxEdge = 10000000;

// 邻接表
struct SparseGraph {
  int num_vertexes; // 顶点数
  int num_edges; // 边数
  map<int, list<int> > mat;
};

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数
  int num_edges; // 边数
  int** mat;
};

// 前向星
struct EdgeNode {
  int from; // 起点
  int to; // 终点
  int weight; // 权重...
  int next;
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

