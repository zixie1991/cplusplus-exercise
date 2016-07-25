#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

void TestCopyCapture() {
  int a = 0;
  //auto f = [=](){a++;};
  auto f = [=]() mutable {a++;};

  f();
  cout << a << endl;
}

int main() {
  TestCopyCapture();
  return 0;
}
