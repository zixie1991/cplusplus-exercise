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

class B0 {

};

class B1: public B0 {

};

class B1Virtual: public virtual B0 {

};

class B2: public B1 {

};

void TestClassMemoryAlignment() {
  // sizeof(): 返回一个对象或类型所占的内存字节数
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

void TestClassSizeof() {
  // 空类和单继承的空类所占空间为1
  cout << "sizeof(B0):" << sizeof(B0) << endl;
  cout << "sizeof(B1):" << sizeof(B1) << endl;
  cout << "sizeof(B2):" << sizeof(B2) << endl;
  // 虚继承的空类所占空间为8(64位机, 涉及续表、虚指针)
  cout << "sizeof(B1Virtual):" << sizeof(B1Virtual) << endl;
}

int main() {
  cout << "sizeof(bool):" << sizeof(bool) << endl;
  cout << "TestClassMemoryAlignment:" << endl;
  TestClassMemoryAlignment();
  cout << "TestClassSizeof:" << endl;
  TestClassSizeof();
  return 0;
}
