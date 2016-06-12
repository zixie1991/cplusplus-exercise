#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 最长回文子串: http://taop.marchtea.com/01.05.html
// Manacher's ALGORITHM: O(n)时间求字符串的最长回文子串: https://www.felix021.com/blog/read.php?2040

// 回文串: 正读和反读都一样的字符串
bool idPalindrome(const char* str) {
  const char* begin = str;
  const char* end = str + strlen(str) - 1;
  while (begin < end) {
    if (*begin != *end) {
      return false;
    }
    begin++;
    end--;
  }

  return true;
}

// 最长回文子串
int LongestPalindrome(const char* str) {
  if (str == NULL) {
    return 0;
  }

  int max = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    int val = 0;
    // 长度为奇数的回文子串
    for (int j = 0; i - j >= 0 && i + j < len; j++) {
      if (str[i-j] == str[i+j]) {
        val = 2 * j + 1;
      }
    }
    if (val > max) {
      max = val;
    }

    // 长度为偶数的回文子串
    for (int j = 0; i - j >= 0 && i + 1 + j < len; j++) {
      if (str[i-j] == str[i+1+j]) {
        val = 2 * j + 2;
      }
    }
    if (val > max) {
      max = val;
    }
  }

  return max;
}

int LongestPalindrome2(const char* str) {
  if (str == NULL) {
    return 0;
  }

  int n = strlen(str);
  char* str2 = (char*)malloc(sizeof(char) * (2 * n + 2));
  str2[0] = '$';
  for (int i = 0; i < n; i++) {
    str2[2 * i + 1] = '#';
    str2[2 * i + 2] = str[i];
  }
  str2[2 * n + 1] = '#';

  // p[i]表示以str2[i]为中心的最长回文子串扩张的长度
  int* p = (int*)malloc(sizeof(int) * (2 * n + 2));
  memset(p, 0, sizeof(p));
  int id = 0; // 最大回文子串的中心
  int mx = 0; // 最大回文子串的上边界(最大回文子串不包括mx)
  for (int i = 1; i < 2 * n + 2; i++) {
    p[i] = mx > i ? min(mx - i, p[2 * id - i]) : 1;
    while (str2[i - p[i]] == str2[i + p[i]]) {
      p[i]++;
    }

    if (i + p[i] > mx) {
      id = i;
      mx = i + p[i];
    } 
  }

  return mx - id;
}

int main() {
  return 0;
}
