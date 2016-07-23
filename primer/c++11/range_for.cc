#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void TestMapRangeFor() {
  cout << "TestMapRangeFor:" << endl;
  map<int, int> m = {{1, 2}, {2, 3}}; // 初始化列表

  for (const auto& val: m) {
    // val type is std::pair
    cout << val.first << " " << val.second << endl;
  }
}

void TestPairVectorRangeFor() {
  cout << "TestPairVectorRangeFor:" << endl;
  vector<pair<int, int>> v = {{1, 1}, {2, 2}};
  for (const auto& val: v) {
    // val type is std::pair
    cout << val.first << " " << val.second << endl;
  }

  for (auto& val: v) {
    val.second++;
  }

  for (const auto& val: v) {
    // val type is std::pair
    cout << val.first << " " << val.second << endl;
  }
}

void TestSetRangeForModify() {
  cout << "TestSetRangeForModify:" << endl;
  set<int> s = {1, 2, 3};
  for (auto& val: s) {
    // std::set的内部元素是只读的, auto& 会被推导为const int&
    //val++;
  }

  for (const auto& val: s) {
    cout << val << endl;
  }
}

void TestVectorRangeForChangeContainer() {
  cout << "TestVectorRangeForChangeContainer:" << endl;
  vector<int> v1 = {1, 2, 3, 4};
  // 遍历过程中, 修改容器(insert, erase)
  for (auto val = v1.begin(); val != v1.end(); ) {
    printf("%p ", val);
    cout << *val << " ";
    if (*val == 2) {
      v1.erase(val);
      cout << endl;
      continue ;
    }
    if (*val == 4) {
      v1.insert(val + 1, 5);
    }
    printf("%p ", val);
    cout << *val << " ";
    printf("%p ", v1.end());
    ++val;
    cout << (val - v1.begin()) << " " << (v1.end() - val) << endl;
  }

  for_each(v1.begin(), v1.end(), [](int val) -> void {cout << val << endl;});
  //for_each(v1.begin(), v1.end(), [](int val) {cout << val << endl;});
}

int main() {
  TestMapRangeFor();
  TestPairVectorRangeFor();
  TestSetRangeForModify();
  TestVectorRangeForChangeContainer();
  return 0;
}
