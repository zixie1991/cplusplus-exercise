#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class B;
class A {
  friend B;
  //private:
  public:
    A() {
      cout << "A::A()" << endl;
    }

    ~A() {
      cout << "A::~A()" << endl;
    }
};

class B: public virtual A {
  public:
    B() {
      cout << "B::B()" << endl;
    }

    ~B() {
      cout << "B::~B()" << endl;
    }
};

class C: public B {
  public:
    C() {
      cout << "C::C()" << endl;
    }

    ~C() {
      cout << "C::~C()" << endl;
    }
};

int main() {
  //B b;
  C c;
  return 0;
}
