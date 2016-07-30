#include <unistd.h>

#include <stdio.h>

// Linux C 函数调用栈
// c函数调用过程原理及函数栈帧分析: http://blog.csdn.net/zsy2020314/article/details/9429707
// C语言函数调用栈(一): http://www.cnblogs.com/clover-toeic/p/3755401.html

int func(int a, int b) {
  int c = a + b;
  return c;
}

// gcc -S -0 main.s test_func_stack.c
// gcc -g -o main test_func_stack.c
// objdump -d main > main.dump
int main() {
  int a;
  int b = 2;

  int c = func(a, b);

  return 0;
}
