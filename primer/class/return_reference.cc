#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class A {
  public:
    A() {
      cout << "A::A()" << endl;
    }

    ~A() {
      cout << "A::~A()" << endl;
    }
};

const A Func1() {
  // 一次构造
  return A();
}

const A Func2() {
  // 一次构造
  A a;
  return a;
}

void TestReturnValue() {
  A a1;
  cout << "---split line---" << endl;
  a1 = Func1();
  cout << "---split line---" << endl;
  a1 = Func2();
}

int main() {
  TestReturnValue();
  return 0;
}
