#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <typeinfo>

using namespace std;

template <typename T1, typename T2>
class Base {
  public:
    Base() {
      cout << typeid(t1_).name() << " " << typeid(t2_).name() << endl;
    }

  private:
    T1 t1_;
    T2 t2_;
};

template <typename T1, typename T2=int>
class Base2 {
  public:
    Base2() {
      cout << typeid(t1_).name() << " " << typeid(t2_).name() << endl;
    }

  private:
    T1 t1_;
    T2 t2_;
};

//template <typename T1=int, typename T2> // no default params for T2
//class Base3 {
  //public:
    //Base3() {
      //cout << typeid(t1_).name() << " " << typeid(t2_).name() << endl;
    //}

  //private:
    //T1 t1_;
    //T2 t2_;
//};

void TestBase() {
  Base<float, int> b1;
  Base2<long> b2;
}

int main() {
  TestBase();
  return 0;
}
