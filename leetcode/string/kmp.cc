#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// KMP 算法
// 字符串匹配之 KMP 和 BM 算法: http://www.oschina.net/question/12_23429?fromerr=ARH1VIkN

char* Strstr(const char* text, const char* pattern) {
  int pattern_len = strlen(pattern); 
  if (pattern_len == 0) {
    return (char*)text;
  }

  while (*text != *pattern || strncmp(text, pattern, pattern_len)) {
    if (*text++ == '\0') {
      return NULL;
    }
  }

  return (char*)text;
}

/**
 * @brief 部分匹配表
 *
 * @param str 搜索词(模式串)
 * @param n 搜索词长度
 * @param next 部分匹配表
 */
void PartialMatch(const char* str, int n, int* next) {
  int j = 0; // j表示前缀
  next[0] = next[1] = j;
  for (int i = 2; i < n; i++) { // i表示后缀
    while (j > 0 && str[j] != str[i-1]) {
      j = next[j];
    }

    if (str[j] == str[i-1]) {
      j++;
    }

    next[i] = j;
  }
}

/**
 * @brief KMP算法
 *
 * @param str1 字符串(文本串)
 * @param n 字符串长度
 * @param str2 搜索词(模式串)
 * @param m 搜索词长度
 *
 * @return 
 */
int KMP(const char* str1, int n, const char* str2, int m) {
  // 部分匹配表
  // next[i]表示str2[0..i-1]的"前缀"和"后缀"的最长公共元素长度
  int* next = (int*)malloc(m * sizeof(int));
  PartialMatch(str2, m, next);
  for (int i = 0; i < m; i++) {
    printf("%d ", next[i]);
  }
  printf("\n");

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
      return i - m + 1; 
    }
  }

  free(next);
  return -1;
}

int main() {
  const char* str1 = "ababacacca";
  const char* str2 = "b";
  cout << KMP(str1, strlen(str1), str2, strlen(str2)) << endl;
  return 0;
}
