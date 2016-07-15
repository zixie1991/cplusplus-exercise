#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 模板方法设计模式
class Base {
  public:
    void Foo() {
      cout << "Do something before." << endl;
      Bar();
      cout << "Do something after." << endl;
    }

  private:
    virtual void Bar() {
      cout << "Base::Bar" << endl;
    }
};

class Derived: public Base {
  private:
    virtual void Bar() {
      cout << "Derived::Bar" << endl;
    }
};

void TestNVI() {
  // non-virtual interface
  Base* b = new Derived();
  b->Foo();
}

int main() {
  TestNVI();
  return 0;
}
