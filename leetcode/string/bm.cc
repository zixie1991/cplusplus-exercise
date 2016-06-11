#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

/**
 * @brief 暴力后缀匹配算法
 *
 * @param text 文本串
 * @param pattern 字符串
 *
 * @return 
 */
char* StrStr(const char* text, const char* pattern) {
  int text_len = strlen(text);
  int pattern_len = strlen(pattern);
  int j = 0;

  while (j <= text_len - pattern_len) {
    int i = pattern_len - 1;
    for (; i >= 0 && text[j + i] == pattern[i]; i--);
    if (i < 0) {
      return (char*)text + j;
    } else {
      j++;
    }
  }

  return NULL;
}

const int CHAR_MAX = 256;

/**
 * @brief 坏字符规则
 *
 * @param pattern
 * @param pattern_len
 * @param bad_char
 */
void BadChar(const char* pattern, int pattern_len, int* bad_char) {
  // 坏字符没有出现在模式串中
  for (int i = 0; i < CHAR_MAX; i++) {
    bad_char[i] = pattern_len;
  }

  // 坏字符出现在模式串中
  for (int i = 0; i < pattern_len; i++) {
    bad_char[(unsigned char)pattern[i]] = pattern_len - 1 - i;
  }
}

/**
 * @brief 好后缀规则
 *
 * @param pattern
 * @param pattern_len
 * @param good_suffix
 */
void GoodSuffix(const char* pattern, int pattern_len, int* good_suffix) {
  // suffix[i]表示以i为边界(包括i)，与模式串后缀的最大匹配长度
  int* suffix = (int*)malloc(sizeof(int) * pattern_len);

  suffix[pattern_len - 1] = pattern_len;
  for (int i = pattern_len - 2; i >= 0; i--) {
    int j = i;
    while (j >= 0 && pattern[j] == pattern[pattern_len - 1 - i + j]) {
      j--;
    }

    suffix[i] = i - j;
  }

  // 没有子串匹配上好后缀, 找不到最大前缀
  for (int i = 0; i < pattern_len; i++) {
    good_suffix[i] = pattern_len;
  }

  // 没有子串匹配上好后缀, 找到最大前缀
  int j = 0;
  for (int i = pattern_len - 1; i >= 0; i--) {
    if (suffix[i] == i + 1) {
      for (; j < pattern_len - 1 - i; j++) {
        if (good_suffix[j] == pattern_len) {
          good_suffix[j] = pattern_len - 1 - i;
        }
      }
    }
  }

  // 有子串匹配上好后缀
  for (int i = 0; i <= pattern_len - 2; i++) {
    good_suffix[pattern_len - 1 - suffix[i]] = pattern_len - 1 - i;
  }
}

/**
 * @brief BM算法
 *
 * @param text 文本串
 * @param pattern 模式串
 */
char* BoyerMoore(const char* text, const char* pattern) {
  int text_len = strlen(text);
  int pattern_len = strlen(pattern);

  // 预处理模式串
  int bad_char[CHAR_MAX];
  BadChar(pattern, pattern_len, bad_char);
  int* good_suffix = (int*)malloc(sizeof(int) * pattern_len);
  GoodSuffix(pattern, pattern_len, good_suffix);

  int j = 0;
  while (j <= text_len - pattern_len) {
    int i = pattern_len - 1;
    for (; i >= 0 && pattern[i] == text[j + i]; i--);

    if (i < 0) {
      return (char*)text + j;
    } else {
      j += max(good_suffix[i], bad_char[(unsigned char)pattern[i]] - (pattern_len - 1 - i));
    }
  }

  return NULL;
}

int main() {
  const char* text = "ababacacca";
  const char* pattern = "b";
  cout << "text: " << text << endl;
  cout << "pattern: " << pattern << endl;
  cout << "bm: " << BoyerMoore(text, pattern) << endl;
  cout << "strstr: " << StrStr(text, pattern) << endl;
  return 0;
}
