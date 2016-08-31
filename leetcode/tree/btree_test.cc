#include "btree.h"

void TestBTreePut() {
  BTree<int, int> btree3(3);
  btree3.Put(1, 1);
  btree3.Print();
  btree3.Put(2, 2);
  btree3.Print();
  btree3.Put(3, 3);
  btree3.Remove(3);
  btree3.Print();
  btree3.Put(9, 9);
  btree3.Put(8, 8);
  btree3.Put(4, 4);
  btree3.Put(5, 5);
  btree3.Put(6, 6);
  btree3.Print();
  btree3.Remove(9);
  btree3.Print();
  for (int i = 10; i < 200; i++) {
    btree3.Put(i, i);
  }
  btree3.Print();
}

int main() {
  BTree<int, int> btree16(16);
  TestBTreePut();
  return 0;
}
