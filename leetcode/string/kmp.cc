#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;


/**
 * @brief 部分匹配表
 *
 * @param str 搜索词
 * @param n 搜索词长度
 * @param next 部分匹配表
 */
void PartialMatch(const char* str, int n, int* next) {
  next[0] = 0;
  int j = 0;
  for (int i = 1; i < n; i++) {
    while (j > 0 && str[j] == str[i]) {
      j = next[j];
    }

    if (str[j] == str[i]) {
      j++;
    }

    next[i] = j;
  }
}

/**
 * @brief KMP算法
 *
 * @param str1 字符串
 * @param n 字符串长度
 * @param str2 搜索词
 * @param m 搜索词长度
 *
 * @return 
 */
int KMP(const char* str1, int n, const char* str2, int m) {
  // 部分匹配表
  int* next = (int*)malloc(n * sizeof(int));
  PartialMatch(str1, n, next);

  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && str1[i] != str2[j]) {
      j = next[j];
    }
    if (str1[i] == str2[j]) {
      j++;
    }
    if (j == m) {
      free(next);
      return i - j + 1; 
    }
  }

  free(next);
  return -1;
}

int main() {
  const char* str1 = "ababc";
  const char* str2 = "abc";
  cout << KMP(str1, strlen(str1), str2, strlen(str2)) << endl;
  return 0;
}
