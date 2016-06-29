#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 冒泡排序
// 稳定排序, 时间: O(n**2)
void BubbleSort(int a[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int flag = 0;
    for (int j = 1; j < n - i; j++) {
      if (a[j-1] > a[j]) {
        int tmp = a[j - 1];
        a[j - 1] = a[j];
        a[j] = tmp;
        flag = 1;
      }
    }

    if (!flag) {
      break;
    }
  }
}

void TestBubbleSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  BubbleSort(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestBubbleSort:" << endl;
  TestBubbleSort();
  return 0;
}
