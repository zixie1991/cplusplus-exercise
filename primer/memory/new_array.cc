#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

using namespace std;

// 浅谈 C++ 中的 new/delete 和 new[]/delete[]: http://www.cnblogs.com/hazir/p/new_and_delete.html
// C/C++内存管理详解: http://chenqx.github.io/2014/09/25/Cpp-Memory-Management/

// 没有析构函数
class A {
};

// 有析构函数
class B {
  public:
    ~B() {}
};

void TestNewArray() {
  const long n = 16;
  A* a = new A[n];
  B* b = new B[n];
  // 64位, 8字节
  size_t* a2 = reinterpret_cast<size_t*>(a);
  size_t* b2 = reinterpret_cast<size_t*>(b);
  
  a2--;
  b2--;

  printf("%ld %lx\n", *a2, *a2);
  // 带析构函数的数组，才会分配多余的8字节(64位)存数组的大小
  printf("%ld %lx\n", *b2, *b2);
}

void TestArray() {
  cout << "TestArray:" << endl;
  int a[] = {1, 2, 3, 4};
  char b[] = "abcd";
  int* c = a;

  cout << a << " " << (a + 1) << " " << (a + 2) << endl;
  cout << b << " " << (b + 1) << " " << (b + 2) << endl;
  cout << c << " " << (c + 1) << " " << (c + 2) << endl;
}

int main() {
  TestNewArray();
  TestArray();
  return 0;
}
