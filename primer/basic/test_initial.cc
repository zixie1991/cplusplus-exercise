#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int i = 1;

void foo() {
  // i是一个未定义的值
  int i = i;
  cout << "foo i=" << i << endl;
}

int main() {
  // i是一个未定义的值
  int i = i;

  cout << "i=" << i << endl;
  foo();
  return 0;
}
