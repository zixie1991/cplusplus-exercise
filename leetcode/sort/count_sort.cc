#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 计数排序: http://www.cppblog.com/shyli/archive/2007/04/03/21130.html

int MaxVal(int a[], int n) {
  int max = a[0];

  for (int i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }

  return max;
}

// 计数排序
// 稳定排序, 时间: O(n+k)
void BucketSort(int a[], int n) {
  int k = MaxVal(a, n);

  int* count = new int[k + 1];
  int* b = new int[n];

  memset(count, 0, sizeof(count));
  for (int i = 0; i < n; i++) {
    count[a[i]]++;
  }

  //for (int i = 1; i <= k; i++) {
    //count[i] += count[i-1];
  //}

  //for (int i = n - 1; i >= 0; i--) {
    //b[--count[a[i]]] = a[i];
  //}

  //for (int i = 0; i < n; i++) {
    //a[i] = b[i];
  //}

  // better method
  int idx = 0;
  for (int i = 0; i <= k; i++) {
    for (int j = 0; j < count[i]; j++) {
      a[idx++] = i;
    }
  }

  delete[] count;
  delete[] b;
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
