#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <iostream>

using namespace std;

// 字节码问题--wchar和char的区别以及wchar和char之间的相互转换字符编码转换等方法及函数介绍
// http://www.cnblogs.com/MichaelOwen/articles/2128771.html

void TestCharArray() {
  cout << "TestCharArray:" << endl;
  char a[] = "中文";
  cout << strlen(a) << endl;
}

/*
 * linux 下 wchar_t和char的相互转化和测试
 * win32下wchar_t占2个字节，linux下wchar_t占4个字节。wchar_t的高字节应该存放在char数组的低字节。
 * Linux下面的没有命名为 WideCharToMultiByte() 和 MultiByteToWideChar() 函数，WideCharToMultiByte，MultiByteToWideChar是windows下的函数，
 * 在linux下也有类似的两个函数：
 * mbstowcs()
 * wcstombs() 
 * 值得注意的是:
 * size_t mbstowcs(wchar_t *wcstr, const char *mbstr, size_t count);
 * 这个函数的第三个参数count，大小一定要是mbstr长度的2倍，否则出来的中文也会是乱码。
 * 
 * wcstombs和mbstowcs使用
 * #include <locale.h>
 * setlocale(LC_ALL, "");
 * wcstombs(char *to, wchar_t *from, size_t _maxCount);
 * mbstowcs(wchar_t *to, char *from, size_t _maxCount);
 * 
 * 还有呢，转码还可以使iconv函数族，包含以下三个函数（其具体实例可以见demo_iconv.c和code_convert.c）：
 * iconv_t iconv_open(const char *tocode, const char *fromcode);
 * size_t iconv(iconv_t cd, char **inbuf, size_t *inbytesleft,char **outbuf, size_t *outbytesleft);
 * int iconv_close(iconv_t cd);
 */
void TestWcharArray() {
  cout << "TestWcharArray:" << endl;
  cout << sizeof(wchar_t) << endl;
  wchar_t a[] = L"中文";
  // wcscmp, wcscpy, wcslen
  cout << wcslen(a) << endl;
}

int main() {
  TestCharArray();
  TestWcharArray();
  return 0;
}
