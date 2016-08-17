#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int CountNumOfOne(int n) {
  int count = 0;
  while (n) {
    count++;
    // 去掉最右边的1个1
    n = n & (n - 1);
  }
}

int main() {
  return 0;
}
