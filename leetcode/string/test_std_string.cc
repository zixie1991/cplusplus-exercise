#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test_string() {
  string str1;
  string str2(10, 'a');
  string str3("abc");
  string str4(str3);
  char a1[] = "1234";
  string str5(a1, a1 + strlen(a1));
  string str6(a1, strlen(a1));

  cout << "str1:" << str1 << endl;
  cout << "str2:" << str2 << endl;
  cout << "str3:" << str3 << endl;
  cout << "str4:" << str4 << endl;
  cout << "str5:" << str5 << endl;
  cout << "str6:" << str6 << endl;
}

void test_vector() {
  vector<char> c_vec1(5, 'a');
  string str1(&c_vec1[0], c_vec1.size());
  vector<char> c_vec2(&str1[0], &str1[0] + str1.size());
  cout << "str1:" << str1 << endl;
  for (int i = 0; i < c_vec2.size(); i++) {
    cout << c_vec2[i] << " ";
  }
  cout << endl;
}

int main() {
  test_string();
  cout << endl;
  test_vector();
  return 0;
}
