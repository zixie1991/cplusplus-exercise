#include <iostream>
#include <vector>

using namespace std;

#define MAX 2

// 初始化为0
int g_a[MAX];

int main() {
  // 数组
  // 随机初始化
  int b[MAX];
  int c[2] = {1, 2};

  for (int i = 0; i < 2; i++) {
    cout << g_a[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < 2; i++) {
    cout << b[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < 2; i++) {
    cout << c[i] << " ";
  }
  cout << endl;


  // vector
  vector<int> vec1;
  // 初始化为0
  vector<int> vec2(2);
  vector<int> vec3(2, 2);

  // 初始化为0, 或保持已有值
  vec1.resize(2);
  for (int i = 0; i < 2; i++) {
    cout << vec1[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < 2; i++) {
    cout << vec2[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < 2; i++) {
    cout << vec3[i] << " ";
  }
  cout << endl;

  // stl
  // string
  // deque 双端队列, 结构相对复杂
  // array c++11

  return 0;
}
