#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>

#include "timer.h"

using namespace std;
using namespace timer;


const int size = 100000;
//const int size = 100000000;

void TestPushBack() {
  cout << "TestPushBack:" << endl;
  vector<float> vec;
  float val = 1.0;
  cout << "vec.capacity=" << vec.capacity() << endl;
  cout << "vec.size=" << vec.size() << endl;

  {
  AutoTimer timer(0, "vector<float> push_back");
  for (int i = 0; i < size; i++) {
    vec.push_back(val);
  }
  }
  cout << "vec.capacity=" << vec.capacity() << endl;
  cout << "vec.size=" << vec.size() << endl;
}

void TestPushBackWithReserve() {
  cout << "TestPushBackWithReserve:" << endl;
  vector<float> vec;
  float val = 1.0;
  // ncrease the capacity of the container to a value that's greater or equal
  // to new_cap.
  vec.reserve(size / 1);
  cout << "vec.capacity=" << vec.capacity() << endl;
  cout << "vec.size=" << vec.size() << endl;

  {
  AutoTimer timer(0, "vector<float> push_back");
  for (int i = 0; i < size; i++) {
    vec.push_back(val);
  }
  }
  cout << "vec.capacity=" << vec.capacity() << endl;
  cout << "vec.size=" << vec.size() << endl;
}

void TestIdxWithReserve() {
  cout << "TestPushBackWithReserve:" << endl;
  vector<float> vec;
  float val = 1.0;
  // ncrease the capacity of the container to a value that's greater or equal
  // to new_cap.
  vec.reserve(size / 1);
  cout << "vec.capacity=" << vec.capacity() << endl;
  cout << "vec.size=" << vec.size() << endl;

  {
  AutoTimer timer(0, "vector<float> idx");
  for (int i = 0; i < size; i++) {
    vec[i] = val;
  }
  }
  cout << "vec.capacity=" << vec.capacity() << endl;
  cout << "vec.size=" << vec.size() << endl;
}

int main() {
  TestPushBack();
  TestPushBackWithReserve();
  TestIdxWithReserve();
  return 0;
}
