#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// C++面试中string类的一种正确写法: http://coolshell.cn/articles/10478.html

// 实现一个String类
// 要求:
// 1. 支持复制、赋值
// 2. 能用作参数、返回值
// 3. 能用作标准库的用户类型

class MyString {
  public:
    // 默认构造函数
    MyString():
      data_(new char[1])
    {
      data_[0] = '\0';
    }

    MyString(const char* str):
      data_(new char[strlen(str) + 1])
    {
      strcpy(data_, str);
    }

    // 复制构造函数
    MyString(const MyString& my_string):
      data_(new char[my_string.size() + 1])
    {
      strcpy(data_, my_string.data_);
    }

    // 析构函数
    ~MyString() {
      if (data_) {
        delete[] data_;
        data_ = NULL;
      }
    }

    // 赋值运算符
    /* MyString& operator=(const MyString& my_string) {
      if (this != &my_string) {
        // 不是同一个实例
        delete[] data_;
        data_ = NULL;

        data_ = new char[my_string.size() + 1];
        strcpy(data_, my_string.data_);
      }

      return *this;
    }*/

    MyString& operator=(const MyString& my_string) {
      if (this != &my_string) {
        // 不是同一个实例
        MyString tmp_string(my_string);

        std::swap(data_, tmp_string.data_);
      }

      return *this;
    }

    // accessor
    int size() const {
      return strlen(data_);
    }

    char* c_str() {
      return data_;
    }

    void swap(MyString& my_string) {
      std::swap(data_, my_string.data_);
    }

  private:
    char* data_;
};

void foo(MyString x)
{
}
 
void bar(const MyString& x)
{
}
 
MyString baz()
{
  MyString ret("world");
  return ret;
}
 
int main()
{
  MyString s0;
  MyString s1("hello");
  MyString s2(s0);
  MyString s3 = s1;
  s3 = s2 = s1;
 
  foo(s1);
  bar(s1);
  foo("temporary");
  bar("temporary");
  MyString s4 = baz();
 
  std::vector<MyString> svec;
  svec.push_back(s0);
  svec.push_back(s1);
  svec.push_back(baz());
  svec.push_back("good job");

  return 0;
}
