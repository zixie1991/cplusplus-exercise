#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 桶排序: https://zh.wikipedia.org/wiki/%E6%A1%B6%E6%8E%92%E5%BA%8F

// 桶排序
// 稳定排序, 时间: O(n)
void BucketSort(int a[], int n) {
}

void TestBucketSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  BucketSort(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestBucketSort:" << endl;
  TestBucketSort();
  return 0;
}
