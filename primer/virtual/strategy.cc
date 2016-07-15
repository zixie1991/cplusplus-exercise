#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class GameCharacter;
class HealthCalcFunc {
  public:
    virtual ~HealthCalcFunc() {
    }

    virtual int calc(const GameCharacter& gc) {
      return 0;
    }
};

class GameCharacter {
  public:
    explicit GameCharacter(HealthCalcFunc* health_func):
      health_func_(health_func)
    {
    }

    virtual ~GameCharacter() {
    }

    int HealthValue() const {
      return health_func_->calc(*this);
    }

  private:
    HealthCalcFunc* health_func_;
};

int main() {
}
