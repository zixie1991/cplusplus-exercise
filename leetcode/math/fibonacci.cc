#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 递归
int FibonacciWithRecursive(int n) {
  if (n <= 0) {
    return 0;
  } 

  if (n == 1) {
    return 1;
  }

  return FibonacciWithRecursive(n - 1) + FibonacciWithRecursive(n - 2);
}

// 循环
int FibonacciWithLoop(int n) {
  if (n <= 0) {
    return 0;
  }

  if (n == 1) {
    return 1;
  }

  int f0 = 0;
  int f1 = 1;

  for (int i = 2; i <= n; i++) {
    int f = f0 + f1;
    f0 = f1;
    f1 = f;
  }

  return f1;
}

void TestFibonacci() {
  int n = 10;
  cout << "FibonacciWithRecursive(" << n << ")=" << FibonacciWithRecursive(n) << endl;
  cout << "FibonacciWithLoop(" << n << ")=" << FibonacciWithLoop(n) << endl;
}

int main() {
  cout << "TestFibonacci:" << endl;
  TestFibonacci();
  return 0;
}
