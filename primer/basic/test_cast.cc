#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <iostream>

using namespace std;


// C++类型转换
// C++中的四种类型转换符: http://www.cnblogs.com/iamccme/archive/2013/05/14/3078743.html
// C++类型转换总结: http://www.cnblogs.com/goodhacker/archive/2011/07/20/2111996.html

void test_c_style() {
  int a = -1;
  unsigned int b = (unsigned int)a;
  printf("b=%u(%x)\n", b, b);
}

void test_cpp_style() {
  int a = -1;
  float b = float(a);
  cout << "b=" << b << endl;
  char c = char(a);
  cout << "c=" << (int)c << endl;
}

void test_static_cast() {
  // 基本数据类型转换
  int a = 1;
  // a和b的二进制表达(存储方式)是不同的
  // 程序员面试宝典里面有解释
  float b = static_cast<float>(a);
  printf("%x %x\n", a, (int&)a);
  printf("%x %x\n", a, (int&)b);
}

int main() {
  cout << "test_c_style:" << endl;
  test_c_style();
  cout << "test_cpp_style:" << endl;
  test_cpp_style();
  cout << "test_static_cast:" << endl;
  test_static_cast();
  return 0;
}
