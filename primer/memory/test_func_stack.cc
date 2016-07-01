#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// Linux C 函数调用栈
// c函数调用过程原理及函数栈帧分析: http://blog.csdn.net/zsy2020314/article/details/9429707

int func(int a, int b) {
  int c = a + b;
  return c;
}

// g++ -S -0 main.s test_func_stack.cc
// g++ -g -o main test_func_stack.cc
// objdump -d main > main.dump
int main() {
  int a;
  int b = 2;

  int c = func(a, b);

  return 0;
}
