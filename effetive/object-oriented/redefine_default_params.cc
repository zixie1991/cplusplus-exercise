#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

namespace raw {

class Shape {
  public:
    enum Color{kRed, kGreen, kBlue};
    virtual void draw(Color color=kRed) const = 0;
};

void Shape::draw(Color color) const {
  cout << "Rectangle::draw " << color << endl;
}

class Rectangle: public Shape {
  public:
    void draw(Color color=kGreen) const {
      cout << "Rectangle::draw " << color << endl;
    }
};

class Circle: public Shape {
  public:
    void draw(Color color) const {
      cout << "Circle::draw " << color << endl;
    }
};

void Test() {
  cout << "raw::Test:" << endl;
  Shape* ps = NULL;
  Shape* pr = new Rectangle();
  Shape* pc = new Circle();
  cout << "---split line---" << endl;
  pr->draw();
  cout << "---split line---" << endl;
  pc->draw();
}

}

namespace good {
}

int main() {
  raw::Test();
  return 0;
}
