#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <iostream>

using namespace std;

// sizeof测试
// C++ 虚函数表解析: http://coolshell.cn/articles/12165.html
// C++ 对象的内存布局: http://coolshell.cn/articles/12176.html
typedef int Dtype;

enum EmptyEnum{};
enum Color{kRed, kBlue, kGreen};

struct EmptyStruct{
};

struct ListNode{
  int val; 
  ListNode* next;
};

class A {
  public:
    Dtype a_;
};

class B: public A {
  public:
    Dtype b_;
};

class C: public A {
  public:
    Dtype c_;
};

class D: public B, public C {
  public:
    Dtype d_;
};

class E: public B {
  public:
    Dtype e_;
};

class AWithVirtualFunc {
  public:
    virtual void Func() {}
    Dtype a_;
};

class BWithVirtualFunc: public AWithVirtualFunc {
  public:
    virtual void Func() {}
    Dtype b_;
};

class CWithVirtualFunc: public AWithVirtualFunc {
  public:
    virtual void Func() {}
    Dtype c_;
};

class DWithVirtualFunc: public BWithVirtualFunc, public CWithVirtualFunc {
  public:
    virtual void Func() {}
    Dtype d_;
};

class EWithVirtualFunc: public BWithVirtualFunc {
  public:
    virtual void Func() {}
    Dtype e_;
};

class BWithVirtualBase: public virtual A {
  public:
    Dtype b_;
};

class CWithVirtualBase: public virtual A {
  public:
    Dtype c_;
};

class DWithVirtualBase: public BWithVirtualBase, public CWithVirtualBase {
  public:
    Dtype d_;
};

class EWithVirtualBase: public BWithVirtualBase {
  public:
    Dtype e_;
};

void func1() {}

void TestBasicType() {
  //void a1; // 错误, void通常用作函形参、返回值
  short a2;
  int a3;
  long a4;
  float a5;
  double a6;
  EmptyEnum a7;
  Color a8;
  EmptyStruct a9;
  ListNode a10;
  const char* a11 = "abc";
  char a12[] = "abc";
  void *p1;

  //cout << "sizeof(void):" << sizeof(func1()) << endl;
  cout << "sizeof(short):" << sizeof(a2) << endl;
  cout << "sizeof(int):" << sizeof(a3) << endl;
  cout << "sizeof(long):" << sizeof(a4) << endl;
  cout << "sizeof(float):" << sizeof(a5) << endl;
  cout << "sizeof(double):" << sizeof(a6) << endl;
  cout << "sizeof(EmptyEnum):" << sizeof(a7) << endl;
  cout << "sizeof(Color):" << sizeof(a8) << endl;
  cout << "sizeof(EmptyStruct):" << sizeof(a9) << endl;
  cout << "sizeof(ListNode):" << sizeof(a10) << endl;
  cout << "sizeof(char*):" << sizeof(a11) << endl;
  cout << "sizeof(char[]):" << sizeof(a12) << endl;
  cout << "sizeof(void*):" << sizeof(p1) << endl;
}

void TestClass() {
  A a;
  B b;
  D d;
  E e;
  AWithVirtualFunc a_with_virtual_func;
  BWithVirtualFunc b_with_virtual_func;
  DWithVirtualFunc d_with_virtual_func;
  EWithVirtualFunc e_with_virtual_func;
  BWithVirtualBase b_with_virtual_base;
  DWithVirtualBase d_with_virtual_base;
  EWithVirtualBase e_with_virtual_base;

  cout << "sizeof(A):" << sizeof(A) << ", sizeof(a):" << sizeof(a) << endl;
  cout << "sizeof(B):" << sizeof(B) << ", sizeof(b):" << sizeof(b) << endl;
  cout << "sizeof(D):" << sizeof(D) << ", sizeof(d):" << sizeof(d) << endl;
  cout << "sizeof(E):" << sizeof(E) << ", sizeof(e):" << sizeof(e) << endl;

  cout << "sizeof(AWithVirtualFunc):" << sizeof(AWithVirtualFunc) << ", sizeof(a_with_virtual_func):" << sizeof(a_with_virtual_func) << endl;
  cout << "sizeof(BWithVirtualFunc):" << sizeof(BWithVirtualFunc) << ", sizeof(b_with_virtual_func):" << sizeof(b_with_virtual_func) << endl;
  cout << "sizeof(DWithVirtualFunc):" << sizeof(DWithVirtualFunc) << ", sizeof(d_with_virtual_func):" << sizeof(d_with_virtual_func) << endl;
  cout << "sizeof(EWithVirtualFunc):" << sizeof(EWithVirtualFunc) << ", sizeof(e_with_virtual_func):" << sizeof(e_with_virtual_func) << endl;

  cout << "sizeof(BWithVirtualBase):" << sizeof(BWithVirtualBase) << ", sizeof(b_with_virtual_base):" << sizeof(b_with_virtual_base) << endl;
  cout << "sizeof(DWithVirtualBase):" << sizeof(DWithVirtualBase) << ", sizeof(d_with_virtual_base):" << sizeof(d_with_virtual_base) << endl;
  cout << "sizeof(EWithVirtualBase):" << sizeof(EWithVirtualBase) << ", sizeof(e_with_virtual_base):" << sizeof(e_with_virtual_base) << endl;
};

int main() {
  cout << "TestBasicType:" << endl;
  TestBasicType();
  cout << "TestClass:" << endl;
  TestClass();
  return 0;
}

