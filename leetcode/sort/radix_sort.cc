#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int MaxBit(int a[], int n) {
  int ret = 0;
  for (int i = 0; i < n; i++) {
    int x = a[i];
    int d = 0;
    while (x) {
      d++;
      x /= 10;
    }

    if (d > ret) {
      ret = d;
    }
  }

  return ret;
}

// 基数排序
// 稳定排序, 时间: O(dn), 空间: O(n)
void RadixSort(int a[], int n) {
  int d = MaxBit(a, n);

  int power = 1;
  int count[10]; 
  int* tmp = new int[n];

  for (int i = 0; i < d; i++) {
    for (int j = 0; j < 10; j++) {
      count[j] = 0;
    }

    for (int j = 0; j < n; j++) {
      int x = a[j] / power;
      x %= 10;
      count[x]++;
    }

    for (int j = 1; j < 10; j++) {
      count[j] += count[j-1];
    }
    
    for (int j = n - 1; j >= 0; j--) {
      int x = a[j] / power;
      x %= 10;
      tmp[--count[x]] = a[j];
    }

    for (int j = 0; j < n; j++) {
      a[j] = tmp[j];
    }

    power *= 10;
  }

  delete[] tmp;
}

struct ListNode {
  int val;
  int next;

  ListNode(): val(0), next(-1) {}
};

void RadixSort2(int a[], int n) {
  int d = MaxBit(a, n);
  ListNode bucket[10];
  ListNode* data = new ListNode[n];
  int power = 1;

  for (int i = 0; i < d; i++) {
    // 清空桶
    for (int j = 0; j < 10; j++) {
      bucket[j].next = -1;
    }
    // 清空数据
    for (int j = 0; j < n; j++) {
      data[j].next = -1;
    }

    // 分配
    for (int j = 0; j < n; j++) {
      int x = a[j] / power;
      x %= 10;
      data[j].next = bucket[x].next;
      data[j].val = a[j];
      bucket[x].next = j;
    }

    // 收集
    int k = 0;
    for (int j = 0; j < 10; j++) {
      if (bucket[j].next != -1) {
        int x = bucket[j].next;
        a[k++] = data[x].val;
        x = data[x].next;
        while (x != -1) {
          a[k++] = data[x].val;
          x = data[x].next;
        }
      }
    }

    power *= 10;
  }

  delete[] data;
}

void TestRadixSort() {
  int a[] = {1, 3, 2, 4, 6, 5};
  int n = 6;
  RadixSort2(a, n);
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestRadixSort:" << endl;
  TestRadixSort();
  return 0;
}
