#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 奇特的模板递归模式(CRTP)
//
template <typename T>
class Base {
};

class Derived: Base<Derived> {
  // attributes and behaviors
};
