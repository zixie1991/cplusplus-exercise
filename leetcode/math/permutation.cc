#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 全排列
// STL系列之十 全排列(百度迅雷笔试题): http://blog.csdn.net/morewindows/article/details/7370155

void Swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

// 全排列
void FullPermutation(int a[], int n, int k) {
  // 不包含重复数字
  if (k == n - 1) {
    for (int i = 0; i < n; i++) {
      cout << a[i] << " ";
    }
    cout << endl;
    return ;
  } 

  for (int i = k; i < n; i++) {
    Swap(a[k], a[i]);
    FullPermutation(a, n, k + 1);
    // backtrace
    Swap(a[k], a[i]);
  }
}

bool IsSwap(int a[], int begin, int end) {
  for (int i = begin; i < end; i++) {
    // 重复出现
    if (a[i] == a[end]) {
      return false;
    }
  }
  return true;
}

// 全排列
void FullPermutation2(int a[], int n, int k) {
  // 包含重复数字
  if (k == n - 1) {
    for (int i = 0; i < n; i++) {
      cout << a[i] << " ";
    }
    cout << endl;
    return ;
  }

  for (int i = k; i < n; i++) {
    if (IsSwap(a, k, i)) {
      Swap(a[k], a[i]);
      FullPermutation2(a, n, k + 1);
      Swap(a[k], a[i]);
    }
  }
}

void Reverse(int a[], int begin, int end) {
  // 左闭右闭
  int left = begin;
  int right = end;
  while (left < right) {
    Swap(a[left++], a[right--]);
  }
}

bool NextPermutation(int a[], int n) {
  // 下一个全排列
  for (int i = n - 2; i >= 0; i--) {
    if (a[i + 1] > a[i]) {
      for (int j = n - 1; j > i; j--) {
        if (a[j] > a[i]) {
          // 交换
          Swap(a[i], a[j]);
          // 反转
          Reverse(a, i + 1, n - 1);
          return true;
        }
      }
    }
  }

  return false;
}

void FullPermutation3(int a[], int n) {
  // 非递归全排列
  //  从小到大排序
  sort(a, a + n);

  do {
    for (int i = 0; i < n; i ++) {
      cout << a[i] << " ";
    }
    cout << endl;
  } while (NextPermutation(a, n));
}

void TestFullPermutation() {
  vector<int> a(4);
  for (int i = 0; i < a.size(); i++) {
    a[i] = i;
  }

  FullPermutation(&a[0], a.size(), 0);
}

void TestFullPermutation2() {
  vector<int> a(4);
  for (int i = 0; i < a.size(); i++) {
    a[i] = i;
  }
  a[1] = 2;

  FullPermutation2(&a[0], a.size(), 0);
}

void TestFullPermutation3() {
  vector<int> a(4);
  for (int i = 0; i < a.size(); i++) {
    a[i] = i;
  }
  a[1] = 2;

  FullPermutation3(&a[0], a.size());
}

int main() {
  cout << "TestFullPermutation:" << endl;
  TestFullPermutation();
  cout << "TestFullPermutation2:" << endl;
  TestFullPermutation2();
  cout << "TestFullPermutation3:" << endl;
  TestFullPermutation3();
  return 0;
}
