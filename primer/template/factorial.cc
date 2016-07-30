#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

template <int n>
class Factorial {
  public:
    enum{value=n*Factorial<n-1>::value};
};

template <>
class Factorial<0> {
  public:
    enum{value=1};
};

int main() {
  Factorial<10> f1;
  cout << f1.value << endl;
  cout << Factorial<5>::value << endl;
  const int n = 4; // n must be a const var or value
  //int n = 4;
  cout << Factorial<n>::value << endl;
  return 0;
}
