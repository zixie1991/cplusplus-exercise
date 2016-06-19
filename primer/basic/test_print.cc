#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

void test_printf() {
  // printf计算参数时, 从右向左压栈
  int a[] = {1, 2, 3, 4};
  int* ptr = a;
  printf("%d, %d\n", *ptr, *(++ptr));
  printf("%d, %d\n", *ptr, *(ptr++));
}

int main() {
  cout << "test_printf:" << endl;
  test_printf();
  return 0;
}
