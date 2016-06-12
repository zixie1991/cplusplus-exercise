#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <bitset>
#include <string>

using namespace std;

// 位运算
// 位操作基础篇之位操作全面总结: http://blog.csdn.net/morewindows/article/details/7354571

// & &= 与
// | |= 或
// ^ ^= 异或
// ~ ~= 取反
// << <<= 左移
// >> >>= 右移

// 判断奇偶
// n & 1 == 0 偶数
// n & 1 != 0 奇数

/**
 * @brief 交换两个整数
 *
 * @param a
 * @param b
 */
void Swap(int& a, int& b) {
  a ^= b;
  b ^= a; // b ^= a1(a1 = a ^ b) => b = b ^ a1 = b ^ (a ^ b) = (b ^ b) ^ a = a
  a ^= b; // a ^= b1(b1 = a) -> a = a1 ^ b1(a1 = a ^ b) = (a ^ b) ^ a = (a ^ a) ^ b = b
}

/**
 * @brief 变换正负
 *
 * @param n
 *
 * @return 
 */
int SignReverse(int n) {
  return ~n + 1;
}

/**
 * @brief 求绝对值
 *
 * @param n
 *
 * @return 
 */
int Abs(int n) {
  return n >> 31 == 0 ? n : ~n + 1;
}

int Abs2(int n) {
  // 非正整数(包括0) >> 31 = 0
  // 负整数 >> 31 = -1 = 0xffffffff
  int i = n >> 31;
  return (n ^ i) - i;
}

// 位图
// int flag[MAX]
// flag[i / 32] = 1 << (i % 32)

// unsigned short a
// 交换高低位: a = (a << 8) | (a >> 8)
// 二进制逆序: 
// a = ((a & 0xAAAA) >> 1) | ((a & 0x5555) << 1)
// a = ((a & 0xCCCC) >> 2) | ((a & 0x3333) << 2)
// a = ((a & 0xF0F0) >> 4) | ((a & 0x0F0F) << 4)
// a = ((a & 0xFF00) >> 8) | ((a & 0x00FF) << 8)
// 二进制中1的个数:
// a = ((a & 0xAAAA) >> 1) + (a & 0x5555)
// a = ((a & 0xCCCC) >> 2) + (a & 0x3333)
// a = ((a & 0xF0F0) >> 4) + (a & 0x0F0F)
// a = ((a & 0xFF00) >> 8) + (a & 0x00FF)

// 利用a^b=b^a, a^a=0, 0^a=a
// 找到数组中出现一次的数(只有一个, 其他数出现2次)
// 找到数组中出现一次的两个数(其他数出现2次)(分组)

// 位运算简介及实用技巧（一）：基础篇: http://www.matrix67.com/blog/archives/263
// 去掉最后一位          | (101101->10110)           | x shr 1
// 在最后加一个0         | (101101->1011010)         | x shl 1
// 在最后加一个1         | (101101->1011011)         | (x shl 1)+1
// 把最后一位变成1       | (101100->101101)          | x or 1
// 把最后一位变成0       | (101101->101100)          | (x or 1)-1
// 最后一位取反          | (101101->101100)          | x xor 1
// 把右数第k位变成1      | (101001->101101,k=3)      | x or (1 shl (k-1))
// 把右数第k位变成0      | (101101->101001,k=3)      | x and not (1 shl (k-1))
// 右数第k位取反         | (101001->101101,k=3)      | x xor (1 shl (k-1))
// 取末三位              | (1101101->101)            | x and 7
// 取末k位               | (1101101->1101,k=5)       | x and (1 shl k-1)
// 取右数第k位           | (1101101->1,k=4)          | x shr (k-1) and 1
// 把末k位变成1          | (101001->101111,k=4)      | x or (1 shl k-1)
// 末k位取反             | (101001->100110,k=4)      | x xor (1 shl k-1)
// 把右边连续的1变成0    | (100101111->100100000)    | x and (x+1)
// 把右起第一个0变成1    | (100101111->100111111)    | x or (x+1)
// 把右边连续的0变成1    | (11011000->11011111)      | x or (x-1)
// 取右边连续的1         | (100101111->1111)         | (x xor (x+1)) shr 1
// 去掉右起第一个1的左边 | (100101000->1000)         | x and (x xor (x-1))

// STL bitset
// boost dynamic_bitset: http://m.blog.csdn.net/article/details?id=8240061
// 《Effective STL》学习笔记（第二部分）: http://dongxicheng.org/cpp/effective-stl-part2/
void test_bitset() {
  // bitset 存储二进制位，但它的大小固定, 支持位运算
  bitset<16> bs1; 
  bitset<16> bs2(10);
  bitset<16> bs3(string("100"));
  const int c = 16;
  constexpr int n = c;
  bitset<n> bs4;

  cout << "bs1:" << bs1 << endl;
  cout << "bs2:" << bs2 << endl;
  cout << "bs3:" << bs3 << endl;
  cout << "bs4:" << bs4 << endl;

  // dynamic bitset size
  // use vector<bool>: vector<bool>不是STL容器, 是元素为bool的vector的特化, 内部并不真正存储bool值, 而是以bit来压缩保存, 使用代理技术来操作bit, 造成的后果就是它很像容器, 大多数情况下的行为与标准容器一致，但它不是容器，不满足容器的定义
  // use boost::dynamic_bitset 保存了vector<bool>和bitset的优点, 填补了它们的不足
}

int main() {
  test_bitset();
  return 0;
}
