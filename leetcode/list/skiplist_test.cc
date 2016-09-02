#include "skiplist.h"

void TestSkipList() {
  SkipList<int, int> skip_list;
  skip_list.Insert(1, 1);
  skip_list.Insert(9, 9);
  skip_list.Insert(4, 4);
  skip_list.Print();
}

int main() {
  TestSkipList();
  return 0;
}
