#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 模板方法设计模式

class GameCharacter;

int DefaultHealthCalc(const GameCharacter& gc) {
  return 0;
}

class GameCharacter {
  public:
    typedef int (*HealthCalcFunc)(const GameCharacter& gc);

    explicit GameCharacter(HealthCalcFunc health_func=DefaultHealthCalc):
      health_func_(health_func)
    {
    }

    int HealthValue() const {
      return health_func_(*this);
    }

  private:
    HealthCalcFunc health_func_;
};

int LoseHealthFast(const GameCharacter& gc) {
  return 2;
}

int LoseHealthSlow(const GameCharacter& gc) {
  return 1;
}

void TestFunctionPointer() {
  GameCharacter gc1;
  cout << gc1.HealthValue() << endl;
  GameCharacter gc2(LoseHealthFast);
  cout << gc2.HealthValue() << endl;
  GameCharacter gc3(LoseHealthSlow);
  cout << gc3.HealthValue() << endl;
}

int main() {
  TestFunctionPointer();
  return 0;
}
