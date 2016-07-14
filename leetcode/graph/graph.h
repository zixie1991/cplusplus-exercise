const int kMaxVertex = 10000;
const int kMaxEdge = 10000000;

// 邻接表
struct SparseGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  map<int, list<int> > mat;
};

// 邻接矩阵
struct DenseGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int** mat;
};

// 前向星
struct EdgeNode {
  int from;
  int to;
  int weight;
  int next;
};

struct ForwardStarGraph {
  int num_vertexes; // 顶点数目
  int num_edges; // 边数目
  int* head;
  EdgeNode* edge;
};
