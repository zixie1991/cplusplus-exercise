#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <typeinfo>

using namespace std;

template <typename T>
void Swap(T& a, T& b) {
  T t = a;
  a = b;
  b = t;
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(a, b);

  cout << a << " " << b << endl;
}

template <typename T>
void Func() {
  T a;
}

// 模板函数默认模板参数 C++11
template <typename T=int>
void Func2() {
  T a;
}

template <typename R=int, typename U>
R Func3(U val) {
  cout << typeid(val).name() << endl;
  return val;
}

void TestFunc() {
  Func<int>();
  Func2();
  Func3(3);
  auto ret2 = Func3<float>(3.0);
  cout << typeid(ret2).name() << endl;
  auto ret3 = Func3<long>(3);
  cout << typeid(ret3).name() << endl;
}

int main() {
  TestSwap();
  TestFunc();
  return 0;
}
