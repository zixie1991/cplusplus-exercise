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

int main() {
  TestSwap();
  return 0;
}
