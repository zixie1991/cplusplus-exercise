#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// const指针和指向const的指针
// const 指针与指向const的指针: http://www.cnblogs.com/younes/archive/2009/12/02/1615348.html

void TestConstValPtr() {
  // 指向const的指针
  const int a = 1;
  int b = 2;

  // 指向const的指针(const总出现在*的左侧)
  const int* p1 = &a; // 推荐写法
  int const *p2 = &a;
  //int* p3 = &a; // invalid conversion from "const int*" to "int*"
  const int* p3; // 可以不初始化

  // 指针指向的内容不能修改
  //*p1 = 2; // compile error
  //*p2 = 2; // compile error

  // 指针本身可以修改
  p1 = &b;
  p2 = &b;
}

void TestPtrIsConst() {
  // const指针
  const int a = 1;
  int b = 2;
  int c = 3;

  // const指针(const出现在*的右侧)
  //int* const p1 = &a; // invalid conversion from "const int*" to "int*"
  int* const p2 = &b;
  //int* const p3; // 必须初始化

  // 指针指向的内容可以修改
  *p2 = 3;

  // 指针本身不可以修改
  //p2 = &b; // compile error
  //p2 = &c; // compile error
}

void TestConstValPtrIsConst() {
  // 指向const的const指针
  const int a = 1;
  int b = 2;
  const int c = 3;

  // 指向const的const指针(const同时出现在*的左侧和右侧)
  const int* const p1 = &a; // 推荐写法
  int const* const p2 = &a;
  const int* const p3 = &b;
  int const* const p4 = &b;
  //const int* const p5; // 必须初始化

  // 指针指向的内容不可以修改
  //*p1 = 3; // compile error
  //*p2 = 3; // compile error

  // 指针本身不可以修改
  //p1 = &c; // compile error
  //p2 = &c; // compile error
}

int main() {
  cout << "TestConstValPtr:" << endl;
  TestConstValPtr();
  cout << "TestPtrIsConst:" << endl;
  TestPtrIsConst();
  cout << "TestConstValPtrIsConst:" << endl;
  TestConstValPtrIsConst();
  return 0;
}
