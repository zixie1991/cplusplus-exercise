#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

void Print1ToMaxOfNDigitsNaive(int n) {
  // n >= 10, 溢出, 需要大数
  int max = 1;

  for (int i = 0; i < n; i++) {
    max *= 10;
  }

  // 后20个
  for (int i = 0; i < 20 && max > i; i++) {
    cout << (max - 1 - i) << " ";
  }
  cout << endl;
}

void TestPrint1ToMaxOfNDigits() {
  Print1ToMaxOfNDigitsNaive(0);
  Print1ToMaxOfNDigitsNaive(1);
  Print1ToMaxOfNDigitsNaive(9);
  Print1ToMaxOfNDigitsNaive(10); // 溢出
}

int main() {
  cout << "TestPrint1ToMaxOfNDigits:" << endl;
  TestPrint1ToMaxOfNDigits();
  return 0;
}
