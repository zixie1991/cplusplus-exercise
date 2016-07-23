#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <map>
#include <typeinfo>

using namespace std;

template <typename T>
class IntMap1: public map<int, T> {
};

template <typename T>
struct IntMap2 {
  typedef map<int, T> value_type;
};

template <typename T>
using IntMap3 = map<int, T>;

void TestMapRename() {
  cout << "TestMapRename:" << endl;
  cout << "typeid(IntMap1) == typeid(IntMap2): " << (typeid(IntMap1<int>) == typeid(IntMap2<int>::value_type)) << endl;
  cout << "typeid(IntMap1) == typeid(IntMap3): " << (typeid(IntMap1<int>) == typeid(IntMap3<int>)) << endl;
  cout << "typeid(IntMap2) == typeid(IntMap3): " << (typeid(IntMap2<int>::value_type) == typeid(IntMap3<int>)) << endl;
  cout << "typeid(map<int, int>) == typeid(IntMap3): " << (typeid(map<int, int>) == typeid(IntMap3<int>)) << endl;
}

int main() {
  TestMapRename();
  return 0;
}
