#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class T1 {
  public:

  private:
    int n_;
};

class T2 {
  public:
    operator T1() {
      T1 t1;
      return t1;
    }

  private:
    int n_;
};

int main() {
  T2 t2;
  T1 t1 = static_cast<T1>(t2);
  return 0;
}
