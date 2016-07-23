#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 可调用对象
// 可转换为函数指针的类对象

class Foo {
  public:
    // 函数指针
    using func = int(*)(int a, int b);

    static int add(int a, int b) {
      return a + b;
    }

    operator func(void) {
      return add;
    }
};

class Bar {
  public:
    using func = void(*)(void);

    static void hello() {
      cout << "hello" << endl;
    }

    operator func(void) {
      return hello;
    }
};

int main() {
  Foo f;
  cout << f(1, 2) << endl;
  Bar b;
  b();
  return 0;
}
