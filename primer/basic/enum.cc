#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

enum Mode {kRead=-1, kWrite, kNew};

void TestCast() {
  Mode m1, m2, m3;
  //m1 = 1;
  m1 = static_cast<Mode>(1); // 强制类型转换
  m2 = static_cast<Mode>(3.0);
  m3 = static_cast<Mode>(false);

  cout << m1 << endl;
  cout << m2 << endl;
  cout << m3 << endl;
}

int main() {
  TestCast();
  return 0;
}
