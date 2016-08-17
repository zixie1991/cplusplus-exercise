#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

// sizeof(union type)等于最长成员的内存长度
union Time {
  float ms;
  long us;
};

class Date {
  public:
    Date() {}
    ~Date() {}

    int day;
    int hour;
    int minute;
};

class Date2 {
  public:
    int day;
    int hour;
    int minute;
};

union Time2 {
  //Date date; // 对象不能有构造函数和析构函数
  Date2 date;
  float ms;
  long us;
};

int main() {
  return 0;
}
