#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

char s0[4];

void func1(char s[]) {
  cout << "func1 sizeof(s):" << sizeof(s) << endl;
}

void func2(char* s) {
  cout << "func2 sizeof(s):" << sizeof(s) << endl;
}

int func3() {
  return 0;
}

void TestStrlen() {
  cout << "sizeof(s0):" << sizeof(s0) << endl;
  char s1[4];
  memset(s1, 'a', sizeof(s1));
  cout << "strlen(s1)=" << strlen(s1) << endl; // 出错
  for (int i = 0; i < 4; i++) {
    cout << s1[i] << " ";
  }
  cout << endl;
  cout << "sizeof(s1):" << sizeof(s1) << endl;
  cout << "sizeof s1:" << sizeof s1 << endl;

  func1(s1);
  func2(s1);

  static char s2[4];
  cout << "sizeof(s2):" << sizeof(s2) << endl;

  cout << "sizeof(string):" << sizeof(string) << endl;
  //cout << "sizeof(func1):" << sizeof(func1) << endl; // sizeof后不能接函数指针
  cout << "sizeof(func3()):" << sizeof(func3()) << endl;
}

int main() {
  cout << "TestStrlen:" << endl;
  TestStrlen();
  return 0;
}
