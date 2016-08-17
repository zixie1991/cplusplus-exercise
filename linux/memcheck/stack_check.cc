#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int main() {
  // valgrind 不对静态数组(分配在栈上)进行边界检测
  // 可以使用cppcheck检测出来
  int a[5];
  a[5] = 1;

  int x;
  cout << (x + 3) << endl;
  if (a[0]) {
  }

  int *b = new int[4];
  b[4] = 0;

  return 0;
}
