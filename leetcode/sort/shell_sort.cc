#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 希尔排序
// 不稳定排序, 时间: O(nlogn)
void ShellSort(int a[], int n) {
  int gap = n;
  while (gap > 1) {
    gap = gap / 3 + 1;
    for (int i = gap; i < n; i++) {
      int j;
      int tmp = a[i];
      for (j = i - gap; j >= 0 && tmp < a[j]; j -= gap) {
        a[j + gap] = a[j];
      }

      a[j + gap] = tmp;
    }
  }
}

void TestShellSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  ShellSort(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestShellSort:" << endl;
  TestShellSort();
  return 0;
}
