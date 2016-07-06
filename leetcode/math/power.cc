#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

class BadInputError {
  public:
    BadInputError() {} 
};

const double EPS = 1e-9;
bool Equal(double x, double y) {
  if (abs(x - y) < EPS) {
    return true;
  }

  return false;
}

double PowerWithUnsignedInt(double base, unsigned int exponent) {
  double ret = 1.0;
  
  for (unsigned int i = 0; i < exponent; i++) {
    ret *= base;
  }

  return ret;
}

double Power(double base, int exponent) {
  if (Equal(base, 0.0)) {
    if (exponent == 0) {
      return 1.0;
    } else if (exponent > 0) {
      return 0.0;
    } else {
      throw BadInputError();
    }
  }

  unsigned int abs_exponent = exponent > 0 ? exponent : -exponent;
  double ret = PowerWithUnsignedInt(base, abs_exponent);
  if (exponent < 0) {
    // 负指数
    ret = 1.0 / ret;
  }

  return ret;
}

double FastPowerWithUnsignedInt(double base, unsigned int exponent) {
  double ret = 1.0;

  while (exponent) {
    if (exponent & 1) {
      ret *= base;
    }

    base *= base;
    exponent >>= 2;
  }

  return ret * base;
}

double FastPower(double base, int exponent) {
  if (Equal(base, 0.0)) {
    if (exponent == 0) {
      return 1.0;
    } else if (exponent > 0) {
      return 0.0;
    } else {
      throw BadInputError();
    }
  }

  unsigned int abs_exponent = exponent > 0 ? exponent : -exponent;
  double ret = FastPowerWithUnsignedInt(base, abs_exponent);
  if (exponent < 0) {
    // 负指数
    ret = 1.0 / ret;
  }

  return ret;
}

void TestPower() {
  // 正常
  cout << Power(1, 2) << ", " << FastPower(1, 2) << endl;
  cout << Power(2, 2) << ", " << FastPower(2, 2) << endl;
  cout << Power(3, 2) << ", " << FastPower(3, 2) << endl;
  // 
  //cout << Power(0, -1) << ", " << FastPower(0, -1) << endl;
  cout << Power(0, 0) << ", " << FastPower(0, 0) << endl;
  cout << Power(0, 1) << ", " << FastPower(0, 1) << endl;
}


int main() {
  cout << "TestPower:" << endl;
  TestPower();
  return 0;
}
