#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

void TestCharArrayWithoutZero() {
  const int n = 5;
  char a[n];
  char b[n];
  for (int i = 0; i < n; i++) {
    a[i] = 'a';
  }
  b[0] = 'b';
  b[1] = 0;

  cout << strlen(a) << endl;
}

int main() {
  TestCharArrayWithoutZero();
  return 0;
}
