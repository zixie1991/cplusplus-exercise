#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <iostream>

using namespace std;

#define SUB(x,y) ((x)-(y))
#define SUB1(x,y) x-y
#define SUB2(x,y) (x-y)

#define SECOND_PER_YEAR (365 * 24 * 60 * 60UL)

void TestAccessBefore() {
#define ACCESS_BEFORE1(x, y, z) *SUB1(&x,y)=z
#define ACCESS_BEFORE2(x, y, z) *SUB2(&x,y)=z
  int a[] = {1, 2, 3, 4, 5, 6};
  //ACCESS_BEFORE1(a[5], 4, 6); // 程序语法错误, compile error
  ACCESS_BEFORE2(a[5], 4, 6); // 正常运行
  for (int i = 0; i < 6; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  cout << "SECOND_PER_YEAR=" << SECOND_PER_YEAR << endl;
}

int main() {
  cout << "TestAccessBefore:" << endl;
  TestAccessBefore();
  return 0;
}
