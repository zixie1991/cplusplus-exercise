#include <stdio.h>

class A {
  public:
    ~A() {
      printf("~A()\n");
    }
};

int main() {
  int* a1 = new int[10];
  A* a2 = new A[10];
  return 0;
}
