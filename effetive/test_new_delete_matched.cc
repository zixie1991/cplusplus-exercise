#include <iostream>

using namespace std;

class Simple {
  public:
    ~Simple() {
      cout << "~Simple()" << endl;
    }
};

class Simple2 {
  public:
};

int main() {
  Simple* simple = new Simple();
  Simple* simple_array = new Simple[10];

  delete simple;
  //delete[] simple; // error, 不确定调用多少次析构函数，出现崩溃
  delete[] simple_array;
  //delete simple_array; // error, 只调用一次析构函数，出现崩溃
  
  Simple2* simple2 = new Simple2();
  Simple2* simple2_array = new Simple2[5];

  //delete simple2;
  delete[] simple2; // error, 不确定调用多少次析构函数(编译器合成)，未出现崩溃
  //delete[] simple2_array;
  delete simple2_array; // error, 值调用一次析构函数(编译器合成), 未出现崩溃

  // new和delete不匹配时，valgrind检测出不匹配的new、delete对, 但未检测到内存泄露

  return 0;
}
