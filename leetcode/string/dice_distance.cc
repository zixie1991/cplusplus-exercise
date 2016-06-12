#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 最小编辑距离
// 最小编辑距离 算法原理: http://lindayi.me/2013/08/19/%E6%9C%80%E5%B0%8F%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB-%E7%AE%97%E6%B3%95%E5%8E%9F%E7%90%86/
// [Leetcode] Edit Distance 最小编辑距离: https://segmentfault.com/a/1190000003741294

int DiceDistance(const char* str1, int n, const char* str2, int m) {
  if (n == 0) {
    return m;
  }

  if (m == 0) {
    return n;
  }

  return min(min(DiceDistance(str1, n - 1, str2, m), DiceDistance(str1, n, str2, m - 1)), DiceDistance(str1, n - 1, str2, m - 1) + (str1[n - 1] == str2[m - 1] ? 0 : 1));
}

int main() {
  return 0;
}
