#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <iostream>

using namespace std;


// C++类型转换
// C++中的四种类型转换符: http://www.cnblogs.com/iamccme/archive/2013/05/14/3078743.html
// C++类型转换总结: http://www.cnblogs.com/goodhacker/archive/2011/07/20/2111996.html

void test_c_style() {
  int a = -1;
  unsigned int b = (unsigned int)a;
  printf("b=%u(%x)\n", b, b);
}

void test_cpp_style() {
  int a = -1;
  float b = float(a);
  cout << "b=" << b << endl;
  char c = char(a);
  cout << "c=" << (int)c << endl;
}

void test_static_cast() {
  // 基本数据类型转换
  int a = 1;
  // a和b的二进制表达(存储方式)是不同的
  // 程序员面试宝典里面有解释
  float b = static_cast<float>(a);
  printf("%x %x\n", a, (int&)a);
  printf("%x %x\n", a, (int&)b);
}

class FeatureExtraction {
  public:
    FeatureExtraction() {}
    void ToString() {
      cout << "Feature Extraction" << endl;
    }
};

typedef void* handle_t;
handle_t CreateFeatureExtraction() {
  FeatureExtraction* feature_extraction = new FeatureExtraction();
  handle_t wrapper_feature_extraction = reinterpret_cast<handle_t>(feature_extraction);

  return wrapper_feature_extraction;
}

void DestroyFeatureExtraction(handle_t handle) {
  FeatureExtraction* inner_feature_extraction = reinterpret_cast<FeatureExtraction*>(handle);
  if (NULL != inner_feature_extraction) {
    delete inner_feature_extraction; 
    inner_feature_extraction = NULL;
  }
}

void test_reinterpert_cast() {
  char *p1 = NULL;
  void* v1 = reinterpret_cast<void*>(p1);
  printf("%p\n", v1);

  FeatureExtraction* feature_extraction = new FeatureExtraction();
  int wrapper_feature_extraction = reinterpret_cast<int&>(feature_extraction);
  FeatureExtraction* inner_feature_extraction = reinterpret_cast<FeatureExtraction*>(wrapper_feature_extraction);
  inner_feature_extraction->ToString();

  handle_t handle = CreateFeatureExtraction();
  DestroyFeatureExtraction(handle);
  handle = NULL;

  cout << "---split line---" << endl;
  int a[] = {1, 2, 3};
  int* b = a;
  //int& c = reinterpret_cast<int&>(b); // 64位机器出现精度丢失
  long& c = reinterpret_cast<long&>(b);
  int* d = reinterpret_cast<int*>(c);
  printf("%p %p %p\n", b, c, d);
}

int main() {
  cout << "test_c_style:" << endl;
  test_c_style();
  cout << "test_cpp_style:" << endl;
  test_cpp_style();
  cout << "test_static_cast:" << endl;
  test_static_cast();
  cout << "test_reinterpert_cast:" << endl;
  test_reinterpert_cast();
  return 0;
}
