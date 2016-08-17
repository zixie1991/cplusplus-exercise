#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class Person {
  public:
    void Speak() const {
      cout << "Person::Speak()" << endl;
    }
};

class Student: public Person {
  public:
    void Speak() const { // 常成员函数
      cout << "Student::Speak" << endl;
    }
};

void IsPerson(const Person& p) {
  p.Speak();
}

int main() {
  return 0;
}
