#include <stdio.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

const int g_a1 = 10; // 代码区, 只读
int g_a2 = 20; // 数据段
int g_a3; // BBS段
static int g_a4 = 40; // 数据段

void foo() {
  const int a5 = 50; // 栈
  int a6 = 60; // 栈
  int a7; // 栈
  static int a8 = 80; // 数据段
  int* a9 = (int*)malloc(sizeof(int)); // 堆
  const char* s1 = "hello, foo"; // 代码区, 只读
  char s2[] = "hello, foo"; // 栈

  int* p_a = (int*)&g_a1;
  int* p_b = (int*)&a5;

  //*p_a = 30; // 段错误
  *p_b = 40;

  fprintf(stderr, "&g_a1=%p\n", &g_a1);
  fprintf(stderr, "&g_a2=%p\n", &g_a2);
  fprintf(stderr, "&g_a3=%p\n", &g_a3);
  fprintf(stderr, "&g_a4=%p\n", &g_a4);
  fprintf(stderr, "&a5=%p\n", &a5);
  fprintf(stderr, "&a6=%p\n", &a6);
  fprintf(stderr, "&a7=%p\n", &a7);
  fprintf(stderr, "&a8=%p\n", &a8);
  fprintf(stderr, "a9=%p\n", a9);
  fprintf(stderr, "s1=%p\n", s1);
  fprintf(stderr, "s2=%p\n", s2);
}

int main() {
  foo();
  return 0;
}
