#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include <iostream>

using namespace std;

// C/C++——strcpy函数的 几种 实现 和 详细 解析: http://www.360doc.com/content/12/0725/10/219024_226333196.shtml
// 面试中经典函数的实现: http://noalgo.info/401.html
// 【面试题】实现memcpy函数: http://my.oschina.net/renhc/blog/36345

// 字符串复制
char* StrCpy(char* dst, const char* src) {
  assert(src != NULL && dst != NULL);
  char* ret = dst;
  while((*dst++ = *src++) != '\0');

  return ret; // 实现链式表达式
}

char* StrNCpy(char* dst, const char* src, int size) {
  assert(src != NULL && dst != NULL);
  char* ret = dst;

  int i = 0;
  while(i++ < size && (*dst++ = *src++) != '\0');

  // src长度不够size
  while (i++ < size) {
    *dst++ = '\0';
  }

  return ret;
}

// 内存拷贝
// 不考虑内存重叠问题
void* MemCpy(void* dst, const void* src, int n) {
  assert(src != NULL && dst != NULL);

  char* c_dst = (char*)dst;
  const char* c_src = (const char*)src;
  while (n-- > 0) {
    *c_dst++ = *c_src++;
  }

  return dst;
}

// 考虑了内存重叠问题
void* MemMove(void* dst, const void* src, int n) {
  assert(src != NULL && dst != NULL);

  char* c_dst = (char*)dst;
  const char* c_src = (const char*)src;

  if (c_src < c_dst && c_src + n  > c_dst) {
    c_dst += n - 1;
    c_src += n - 1;
    while (n-- > 0) {
      *c_dst-- = *c_src;
    }
  } else {
    while (n-- > 0) {
      *c_dst++ = *c_src++;
    }
  }

  return dst;
}

// 内存初始化
void* MemSet(void* src, int c, int n) {
  assert(src != NULL);

  char* c_src = (char*)src;
  for (int i = 0; i < n; i++) {
    *c_src++ = (char)c; 
  }

  return src;
}

// 字符串长度
int StrLen(const char* src) {
  assert(src != NULL);
  int len = 0;
  while (*src++ != '\0') {
    len++;
  }

  return len;
}

int StrLen2(const char* src) {
  assert(src != NULL);
  const char* ptr = src;
  while (*ptr++ != '\0');

  return ptr - src - 1; // 使用指针计算长度
}

int StrLen3(const char* src) {
  // 递归实现
  return *src == '\0' ? 0 : StrLen3(++src) + 1;
}

int Atoi(const char* str) {
  int num = 0; // 数值
  int sign = 1; // 符号
  int i = 0;
  int len = strlen(str);

  // 处理' '
  while (str[i] == ' ' && i < len) {
    i++;
  }

  // 处理'+', '-'
  if (str[i] == '+') {
    i++;
  }
  if (str[i] == '-') {
    sign = -1;
    i++;
  }

  for (; i < len; i++) {
    // 处理非数字字符
    if (str[i] < '0' || str[i] > '9') {
      break;
    }

    // 处理越界
    // INT_MAX = ~(1 << 31)
    // INT_MIN = 1 << 31
    if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
      return sign > 0 ? INT_MAX : INT_MIN;
    }

    num = num * 10 + str[i] - '0';
  }

  return sign * num;
}

int main() {
  return 0;
}
