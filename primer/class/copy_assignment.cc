#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class Empty {
  public:
    int a;
};

void TestEmpty() {
  Empty a;
  Empty b;
  Empty c;
  a = b = c;
}

class A {
  public:
    A(int n):
      n_(n)
    {
    }
    A& operator=(const A& a) {
      cout << a.n_ << endl;
      n_ = a.n_;
    }

    int n_;
};

void TestAssignment() {
  A a(1);
  A b(2);
  A c(3);
  c = b = a;

  cout << a.n_ << " " << b.n_ << " " << c.n_ << endl;
}

int main() {
  TestAssignment();
  return 0;
}
