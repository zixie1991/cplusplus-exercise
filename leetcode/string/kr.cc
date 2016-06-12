#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;


// Karp Rabin算法
//  字符串匹配算法SMA 总结之二：KR ，Karp Rabin 算法: http://blog.csdn.net/onezeros/article/details/5531354
// KR算法对模式串和循环中每一次要匹配的子串按一定的hash函数求值，如果hash值相同，才进一步比较这两个串是否真正相等

char* KarpRabin(const char* text, const char* pattern) {
  int text_len = strlen(text);
  int pattern_len = strlen(pattern);

  int hash_text = 0;
  int hash_pattern = 0;

  // hash
  for (int i = 0; i < pattern_len; i++) {
    hash_pattern = (hash_pattern << 1) + (unsigned char)pattern[i];
    hash_text = (hash_text << 1) + (unsigned char)text[i];
  }

  int hash_const = 1 << (pattern_len - 1);

  // search
  for (int i = 0; i <= text_len - pattern_len; i++) {
    if (hash_text == hash_pattern && !strncmp(text + i, pattern, pattern_len)) {
      return (char*)text + i;
    } else {
      // rehash
      hash_text = ((hash_text - text[i] * hash_const) << 1) + text[pattern_len + i];
    }
  }

  return NULL;
}

int main() {
  const char* text = "ababacacca";
  const char* pattern = "b";
  cout << "text: " << text << endl;
  cout << "pattern: " << pattern << endl;
  cout << "kr: " << KarpRabin(text, pattern) << endl;
  return 0;
}
