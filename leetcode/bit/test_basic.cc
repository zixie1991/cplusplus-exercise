#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 基本位运算
void TestBit() {
  // 负数转正数: 取反加一
  int a1 = 100;
  // 正数转负数: 取反加一
  int a2 = -100;
  // 有符号转无符号, 直接拷贝
  unsigned int a3 = a1;
  unsigned int a4 = a2;
  // 无符号转有符号, 直接拷贝
  int a5 = a3;
  int a6 = a4;

  printf("a1=%x, a2=%x, a3=%x, a4=%x, a5=%x, a6=%x\n", a1, a2, a3, a4, a5, a6);
  // ~
  printf("~a1=%x, ~a2=%x\n", ~a1, ~a2);
  // & &=
  printf("a1&a2=%x\n", a1 & a2);
  // | |=
  printf("a1|a2=%x\n", a1 | a2);
  // ^ ^=
  printf("a1^a2=%x\n", a1 ^ a2);
  // <<
  printf("a1<<2=%x, a2<<2=%x\n", a1 << 2, a2 << 2);
  // >> 负数右移，左边补1
  printf("a1>>2=%x, a2>>2=%x\n", a1 >> 2, a2 >> 2);
}

int main() {
  cout << "TestBit:" << endl;
  TestBit();
  return 0;
}
