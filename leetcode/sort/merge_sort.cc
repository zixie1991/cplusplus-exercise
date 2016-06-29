#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 归并排序
// 稳定排序, 时间: O(nlogn), 空间: O(n)
void MergeSort(int a[], int begin, int end) {
  // 左闭右开
  if (begin >= end - 1) {
    return ;
  }

  int mid = (begin + end) / 2;
  MergeSort(a, begin, mid);
  MergeSort(a, mid + 1, end);

  // merge
  int* tmp = new int[end - begin];
  for (int i = begin; i < end; i++) {
    tmp[i] = a[i];
  }

  int i = begin;
  int j = mid;
  int k = 0;
  while (i < mid && j < end) {
    if (tmp[i] > tmp[j]) {
      a[k++] = tmp[i++];
    } else {
      a[k++] = tmp[j++];
    }
  }

  while (i < mid) {
    a[k++] = tmp[i++];
  }

  while (j < end) {
    a[k++] = tmp[j++];
  }

  delete[] tmp;
}

void TestMergeSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  MergeSort(a, 0, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestMergeSort:" << endl;
  TestMergeSort();
  return 0;
}
