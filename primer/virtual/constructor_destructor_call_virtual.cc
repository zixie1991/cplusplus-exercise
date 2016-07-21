#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

class A {
  public:
    A() {
      cout << "A()" << endl;
      // 构造函数内的虚函数不是虚函数
      Foo();
    }

    virtual ~A() {}

    virtual void Foo() {
      cout << "A::Foo()" << endl;
    }
};

class B: public A {
  public:
    // 调用父类构造函数是该类还是父类，而不是子类
    B() {
      cout << "B()" << endl;
      cstr_ = new char[2];
      cstr_[0] = 'A';
      cstr_[1] = '\0';
    }

    ~B() {
      if (!cstr_) {
        delete[] cstr_;
        cstr_ = NULL;
      }
    }    

    void Foo() {
      cout << "B::Foo()" << endl;
      cout << str_ << endl;
      cout << cstr_ << endl;
    }

  private:
    string str_;
    char* cstr_;
};

int main() {
  A* a1;
  cout << "---split line---" << endl;
  B* b = new B();
  cout << "---split line---" << endl;
  A* a2 = b;
  a2->Foo();
  return 0;
}
