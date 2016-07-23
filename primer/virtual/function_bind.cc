#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <functional>

using namespace std;

// 前向声明
class GameCharacter;

short DefaultHealthCalc(const GameCharacter& gc) {
  return 0;
}

class GameCharacter {
  public:
    typedef function<int (const GameCharacter&)> HealthCalcFunc;
    explicit GameCharacter(HealthCalcFunc health_func=DefaultHealthCalc):
      health_func_(health_func)
    {
    }

    int HealthValue() {
      return health_func_(*this);
    }

  private:
    HealthCalcFunc health_func_;
};

class FastCharacter {
  public:
    float HealthValue(const GameCharacter& gc) {
      return 2.0;
    }
};

class SlowHealth {
  public:
    int operator()(const GameCharacter& gc) {
      return 1;
    }
};

void Print(int x, int y) {
  cout << x << " " << y << endl;
}

void TestFunctionAndBind() {
  // 函数指针
  bind(Print, 1, 2)();

  GameCharacter gc1;
  cout << gc1.HealthValue() << endl;
  // 成员函数指针
  FastCharacter fc;
  GameCharacter gc2(bind(&FastCharacter::HealthValue, fc, placeholders::_1));
  cout << gc2.HealthValue() << endl;
  // 函数对象
  SlowHealth sh;
  GameCharacter gc3(bind(sh, placeholders::_1));
  cout << gc3.HealthValue() << endl;
}

int main() {
  TestFunctionAndBind();
  return 0;
}
