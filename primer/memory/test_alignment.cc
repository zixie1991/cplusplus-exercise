#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 内存对齐
// C++ 内存对齐: http://www.cnblogs.com/TenosDoIt/p/3590491.html

class A1 {
  public:
    int i;
    short s;
    char c;
};

class A2 {
  public:
    int i;
    char c;
    short s;
};

class A3 {
  public:
    short s;
    int i;
    char c;
};

class A4 {
  public:
    short s;
    char c;
    int i;
};

class A5 {
  public:
    char c;
    int i;
    short s;
};

class A6 {
  public:
    char c;
    short s;
    int i;
};

void TestClassMemoryAlignment() {
  cout << "sizeof(A1):" << sizeof(A1) << endl;
  A1 a1;
  printf("i=%p, s=%p, c=%p\n", &a1.i, &a1.s, &a1.c);
  cout << "sizeof(A2):" << sizeof(A2) << endl;
  A2 a2;
  printf("i=%p, c=%p, s=%p\n", &a2.i, &a2.c, &a2.s);
  cout << "sizeof(A3):" << sizeof(A3) << endl;
  cout << "sizeof(A4):" << sizeof(A4) << endl;
  cout << "sizeof(A5):" << sizeof(A5) << endl;
  cout << "sizeof(A6):" << sizeof(A6) << endl;
}

int main() {
  cout << "sizeof(bool):" << sizeof(bool) << endl;
  cout << "TestClassMemoryAlignment:" << endl;
  TestClassMemoryAlignment();
  return 0;
}
