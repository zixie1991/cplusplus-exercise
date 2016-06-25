#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <stdexcept>

using namespace std;

// 异常对象

typedef bool BoolError;
typedef int IntError;
typedef float FloatError;

class Error {
  public:
    Error():
      str_("Error()")
    {}

    Error(const string& str):
      str_(str)
    {}

    virtual ~Error() {}

    virtual string str() {
      return str_;
    }

    void set_str(const string& str) {
      str_ = str;
    }

  private:
    string str_;
};

void TestBasicError() {
  try {
    throw BoolError();
  } catch (BoolError) {
  } catch (IntError) { // 不支持算术类型转换, 也不支持类类型转换
  } catch (FloatError) {

  }
}

void TestDeriveError() {
  try {
    throw Error();
    //throw IntError(1);
  } catch (Error& e) {
    cerr << e.str() << endl;
    e.set_str("throw " + e.str());
    throw ; // 重新抛出
  }
}

int main() {
  cout << "TestBasicError:" << endl;
  TestBasicError();
  cout << "TestDeriveError:" << endl;
  try {
    TestDeriveError();
  } catch (Error e) {
    cerr << e.str() << endl;
  } catch (...) {
    cerr << "捕获所有异常代码" << endl;
  }

  return 0;
}
