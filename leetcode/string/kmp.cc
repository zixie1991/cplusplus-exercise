#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// KMP 算法
// 字符串匹配之 KMP 和 BM 算法: http://www.oschina.net/question/12_23429?fromerr=ARH1VIkN

/**
 * @brief 暴力前缀匹配
 *
 * 时间复杂度 O(n*m)
 *
 * @param text 文本串
 * @param pattern 模式串
 *
 * @return 
 */
char* StrStr(const char* text, const char* pattern) {
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
 * @param pattern 模式串
 * @param pattern_len 模式串长度
 * @param next 部分匹配表
 */
void PartialMatch(const char* pattern, int pattern_len, int* next) {
  int j = 0; // j表示前缀
  next[0] = next[1] = j;
  for (int i = 2; i < pattern_len; i++) { // i表示后缀
    while (j > 0 && pattern[j] != pattern[i-1]) {
      j = next[j];
    }

    if (pattern[j] == pattern[i-1]) {
      j++;
    }

    next[i] = j;
  }
}

/**
 * @brief KMP算法
 *
 * @param text 字符串(文本串)
 * @param pattern 搜索词(模式串)
 *
 * @return 
 */
char* KMP(const char* text, const char* pattern) {
  int text_len = strlen(text);
  int pattern_len = strlen(pattern);
  // 部分匹配表
  // next[i]表示pattern[0..i-1]的"前缀"和"后缀"的最长公共元素长度
  int* next = (int*)malloc(pattern_len * sizeof(int));
  PartialMatch(pattern, pattern_len, next);

  int j = 0;
  for (int i = 0; i < text_len; i++) {
    while (j > 0 && text[i] != pattern[j]) {
      j = next[j];
    }
    if (text[i] == pattern[j]) {
      j++;
    }
    if (j == pattern_len) {
      free(next);
      return (char*)text + i - pattern_len + 1; 
    }
  }

  free(next);
  return NULL;
}

int main() {
  const char* text = "ababacacca";
  const char* pattern = "b";
  cout << "text: " << text << endl;
  cout << "pattern: " << pattern << endl;
  cout << "kmp: " << KMP(text, pattern) << endl;
  cout << "strstr: " << StrStr(text, pattern) << endl;
  return 0;
}
