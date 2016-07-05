#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 快速排序
// 不稳定排序, 时间: O(nlogn)
void QuickSort(int a[], int begin, int end) {
  // 左闭右开
  if (begin >= end - 1) {
    return ;
  }

  int left = begin;
  int right = end - 1;
  int pivot = a[left];

  while (left < right) {
    // 右侧子序列的值大于等于pivot
    while (left < right && a[right] >= pivot) right--;
    a[left] = a[right];
    // 左侧子序列的值小于等于pivot
    while (left < right && a[left] <= pivot) left++;
    a[right] = a[left];
  }
  a[left] = pivot;

  QuickSort(a, begin, left);
  QuickSort(a, left + 1, end);
}

int RandomIndex(int begin, int end) {
  // 左闭右开
  return begin + random() % (end - begin);
}

// 快排另一种实现
void QuickSort2(int a[], int begin, int end) {
  if (begin >= end - 1) {
    return ;
  }

  int small = RandomIndex(begin, end);
  swap(a[small], a[end - 1]);
  small = begin - 1;
  for (int index = begin; index < end - 1; index++) {
    if (a[index] < a[end - 1]) {
      ++small;
      swap(a[small], a[index]);
    }
  }

  ++small;
  swap(a[small], a[end - 1]);

  QuickSort2(a, begin, small);
  QuickSort2(a, small + 1, end);
}


void TestQuickSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  //QuickSort(a, 0, n);
  QuickSort2(a, 0, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestQuickSort:" << endl;
  TestQuickSort();
  return 0;
}
