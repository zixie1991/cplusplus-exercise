#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void TestIterAndErase() {
  int a1[] = {1, 2, 3, 4, 5};
  vector<int> vec1(a1, a1 + 5);

  printf("vec1: %p %p %ld\n", &vec1[0], &vec1[vec1.size()], &vec1[vec1.size()] - &vec1[0]);
  for (vector<int>::iterator iter = vec1.begin(); iter != vec1.end(); ++iter) {
    cout << *iter << " ";
    iter = vec1.erase(iter);
    break;
  }
  cout << endl;

  string str1 = "12345";
  vector<char> vec2(&str1[0], &str1[0] + str1.size());
  for (vector<char>::iterator iter = vec2.begin(); iter != vec2.end(); ++iter) {
    cout << *iter << " ";
  }
  cout << endl;
}

int main() {
  cout << "TestIterAndErase:" << endl;
  TestIterAndErase();
  return 0;
}
