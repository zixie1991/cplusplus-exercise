#include "bplustree.h"

#include <vector>
#include <iostream>

using namespace std;

void TestBPlusTreePut() {
  BPlusTree<int, int> bplustree3(3);
  bplustree3.Put(1, 1);
  bplustree3.Print();
  bplustree3.Put(2, 2);
  bplustree3.Print();
  bplustree3.Put(3, 3);
  bplustree3.Print();
  bplustree3.Remove(3);
  bplustree3.Print();
  bplustree3.Put(9, 9);
  bplustree3.Put(8, 8);
  bplustree3.Put(4, 4);
  bplustree3.Put(5, 5);
  bplustree3.Put(6, 6);
  bplustree3.Print();

  for (int i = 10; i < 100; i++) {
    bplustree3.Put(i, i);
  }
  bplustree3.Print();
  bplustree3.Remove(95);
  bplustree3.Print();
  //bplustree3.Remove(99);
  //bplustree3.Remove(98);
  bplustree3.Print();

  vector<int> values;
  bplustree3.RangeGet(79, 98, &values);
  for (auto &iter: values) {
    cout << iter << " ";
  }
  cout << endl;
}

int main() {
  BPlusTree<int, int> bplustree3(3);
  TestBPlusTreePut();
  return 0;
}
