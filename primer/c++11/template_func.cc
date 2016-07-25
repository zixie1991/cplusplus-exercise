#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <typeinfo>

using namespace std;

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

template <typename U1=int, typename U2>
void Func4(U1 val1, U2 val2) {
  cout << typeid(val1).name() << " " << typeid(val2).name() << endl;
}

void TestFunc() {
  Func<int>();
  Func2();
  Func3(3);
  cout << "---split line---" << endl;
  auto ret2 = Func3<float>(3.0);
  cout << typeid(ret2).name() << endl;
  cout << "---split line---" << endl;
  auto ret3 = Func3<long>(3);
  cout << typeid(ret3).name() << endl;
  cout << "---split line---" << endl;
  Func4<float>(1.2, 1.2);
  cout << "---split line---" << endl;
  Func4<long>(1.2, 1.2);
}

int main() {
  TestFunc();
  return 0;
}
