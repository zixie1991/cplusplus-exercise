#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string.h>

class SealedC {
  public:
    static SealedC* Create() {
      return new SealedC();
    }

    static void Destroy(SealedC* sealed_c) {
      if (sealed_c) {
        delete sealed_c;
        sealed_c = NULL;
      }
    }

  private:
    SealedC() {}
    ~SealedC() {}
};

// 密封
template<typename T>
class SealedWithTemplate {
  public:
    friend T;

  private:
    SealedWithTemplate() {}
    ~SealedWithTemplate() {}
};

// 虚继承
class SealedA: public virtual SealedWithTemplate<SealedA> {
  public:
    SealedA() {}
    ~SealedA() {}
};

class B: public SealedA {
  public:
    B() {}
    ~B() {}
};

void TestSealedWithTemplate() {
  B b; // compile error
}

int main() {
  return 0;
}
