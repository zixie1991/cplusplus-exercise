#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 直接插入排序
// 稳定排序, 时间O(n**2)
void InsertSort(int a[], int n) {
  for (int i = 1; i < n; i++) {
    int tmp = a[i];
    int j;
    for (j = i - 1; j >= 0 && tmp < a[j]; j--) {
      a[j+1] = a[j];
    }
    a[j+1] = tmp;
  }
}

// 二分插入排序
// 稳定排序, 时间O(n*log2n)
void BinaryInsertSort(int a[], int n) {
  for (int i = 1; i < n; i++) {
    int tmp = a[i];
    int left = 0;
    int right = i - 1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (tmp < a[mid]) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    // move
    for (int j = i - 1; j >= left; j--) {
      a[j+1] = a[j];
    }

    a[left] = tmp;
  }
}

void TestInsertSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  //InsertSort(a, n);
  BinaryInsertSort(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestInsertSort:" << endl;
  TestInsertSort();
  return 0;
}
