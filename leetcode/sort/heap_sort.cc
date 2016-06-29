#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

void AdjustHeap(int a[], int i, int n) {
  int father = a[i];
  int child_idx = 2 * i + 1; // left son

  while (child_idx < n) {
    // max son
    if (child_idx + 1 < n && a[child_idx + 1] > a[child_idx]) {
      child_idx = child_idx + 1;
    }

    if (a[child_idx] > father) {
      a[i] = a[child_idx];
      i = child_idx;
      child_idx = 2 * i + 1;
    } else {
      break;
    }
  }

  a[child_idx] = father;
}

// 堆排序
// 不稳定排序, 时间: O(nlogn)
void HeapSort(int a[], int n) {
  // 重建堆
  for (int i = n / 2 - 1; i >= 0; i--) {
    AdjustHeap(a, i, n);
  }

  for (int i = n - 1; i >= 0; i--) {
    // 堆顶
    swap(a[i], a[0]);
    AdjustHeap(a, 0, i);
  }
}

void TestHeapSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  HeapSort(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestHeapSort:" << endl;
  TestHeapSort();
  return 0;
}
