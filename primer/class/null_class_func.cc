#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class A {
  public:
    void Print() {
      cout << "A::Print()" << endl;
    }
};


class B {
  public:
    virtual void Print() {
      cout << "B::Print()" << endl;
    }
};

class C {
  public:
    void Print() {
      n_ = 1;
      cout << "C::Print()" << endl;
    }

  private:
    int n_;
};

int main() {
  A *a = NULL;
  cout << sizeof(a) << endl;
  a->Print();

  B *b = NULL;
  cout << sizeof(b) << endl;
  b->Print(); // error, virtual pointer

  C *c = NULL;
  c->Print(); // error, memeber var
  return 0;
}
