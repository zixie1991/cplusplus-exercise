#include <stdio.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

// 从caffe中学习宏定义，宏函数: http://blog.csdn.net/u014114990/article/details/47834507

// 防止头文件(.h)重复定义
//#ifndef HEADER_H_
//#define HEADER_H_
//... 
//#endif

// 宏常量, 推荐const 常量替代宏常量
#define PI 3.1415926

// 宏函数, 避免函数调用, 提高程序效率
#define max(x, y) ((x) > (y) ? (x) : (y))

// 定义局部变量, 使用多个语句
#define swap(x, y) do \
{ \
int tmp = x; \
x = y; \
y = tmp; \
} while(0)

// #将宏参数字符串化
#define STRING(name) #name

// ##连接符
#define INSTANCE(name) \
  int g_##name

// 由于没有对变参起名，我们用默认的宏__VA_ARGS__来替代它
#define LOG_DEBUG(fmt, ...) do \
{ \
  fprintf(stderr, "[DEBUG %s:%d]: "fmt"\n", __FILE__, __LINE__, ##__VA_ARGS__); \
} while(0)

// 我们显式地命名变参为args
#define LOG_INFO(fmt, args...) do \
{ \
  fprintf(stderr, "[INFO %s:%d]: "fmt"\n", __FILE__, __LINE__, ##args); \
} while(0)


int main() {
  // 调试信息
#ifdef DEBUG
  fprintf(stderr, "Debug information. var=%s\n", STRING(a));
#endif
  int a = 1;
  int b = 2;
  cout << "max(" << a << ", " << b << ")=" <<max(a, b) << endl;
  cout << "a=" << a << ", b=" << b << endl;
  swap(a, b);
  cout << "after swap, a=" << a << ", b=" << b << endl;
  // 取消宏定义
#undef DEBUG

#ifdef DEBUG
  fprintf(stderr, "Debug information.\n");
#endif
  INSTANCE(c);
  cout << g_c << endl;

  LOG_DEBUG("a=%d, b=%d", a, b);
  LOG_INFO("c=%d", g_c);
  LOG_DEBUG("hello\n");

  return 0;
}
