#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 选择排序
// 不稳定排序, 时间: O(n**2)
void SelectSort(int a[], int n) {
  for (int i = 0; i < n; i++) {
    int max_idx = i;
    // find max
    for (int j = i + 1; j < n; j++) {
      if (a[j] < a[max_idx]) {
        max_idx = j;
      }
    }

    if (max_idx != i) {
      // swap
      int tmp = a[i];
      a[i] = a[max_idx];
      a[max_idx] = tmp;
    }
  }
}

void TestSelectSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  SelectSort(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestSelectSort:" << endl;
  TestSelectSort();
  return 0;
}
