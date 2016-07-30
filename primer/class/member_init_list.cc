#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class A {
  public:
    A():
      a_(Init())
    {
    }

    int Init() {
      a_ = 1;
      b_ = 2;
      return -1;
    }

    void Print() {
      cout << a_ << " " << b_ << endl;
    }

  private:
    int a_;
    int b_;
};

int main() {
  A a;
  a.Print();
  return 0;
}
