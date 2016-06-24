#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// 析构函数是不能抛异常的!!!
// 不能在析构函数里面抛出异常: http://blog.csdn.net/tianmohust/article/details/8706203
// 是否能在构造函数，析构函数中抛出异常: http://www.cnblogs.com/KevinSong/p/3323372.html

class FuncError: public runtime_error {
  public:
    FuncError(const string& str):
      runtime_error(str)
    {

    }
};

class DestructorError: public runtime_error {
  public:
    DestructorError(const string& str):
      runtime_error(str)
    {

    }
};

class Foo {
  public:
    ~Foo() {
      cout << "~Foo()" << endl;
    }

    void foo() {
      cout << "foo()" << endl;
    }

    void bar() {
      cout << "bar()" << endl;
      throw FuncError("bar() exception");
    }
};

class FooWithException {
  public:
    ~FooWithException() {
      cout << "~FooWithException()" << endl;
      throw DestructorError("~FooWithException() exception");
    }

    void foo() {
      cout << "foo()" << endl;
    }

    void bar() {
      cout << "bar()" << endl;
      throw FuncError("bar() exception");
    }
};

class FooWithWrapperException {
  public:
    ~FooWithWrapperException() {
      cout << "~FooWithWrapperException()" << endl;
      // 把异常完全封装在析构函数内部
      try {
        throw DestructorError("~FooWithWrapperException() exception");
      } catch (runtime_error& e) {
        cerr << e.what() << endl;
      }
    }

    void foo() {
      cout << "foo()" << endl;
    }

    void bar() {
      cout << "bar()" << endl;
      throw FuncError("bar() exception");
    }
};

void TestFoo() {
  try {
    Foo foo;
    foo.foo();
    foo.bar();
  } catch (runtime_error& e) {
    cerr << e.what() << endl;
  }
}

void TestFooWithException() {
  try {
    FooWithException foo;
    foo.foo();
    foo.bar(); // 抛出异常
  } catch (runtime_error& e) {
    // 只捕获到foo.bar()抛出的异常
    // 而忽略了析构函数抛出的异常, 程序崩溃(而且该异常并未继续往外抛)
    cerr << e.what() << endl;
  }
  // 如果对象在运行期间出现了异常，C++异常处理模型有责任清除那些由于出现异常所
  // 导致的已经失效了的对象（也即对象超出了它原来的作用域），并释放对象原来所分
  // 配的资源，这就是调用这些对象的析构函数来完成释放资源的任务，所以从这个意义
  // 上说，析构函数已经变成了异常处理的一部分。不知大家是否明白了这段话所蕴含的
  // 真正内在涵义没有，那就是上面的论述C++异常处理模型它其实是有一个前提假设——
  // 析构函数中是不应该再有异常抛出的。试想！如果对象出了异常，现在异常处理模块
  // 为了维护系统对象数据的一致性，避免资源泄漏，有责任释放这个对象的资源，调用
  // 对象的析构函数，可现在假如析构过程又再出现异常，那么请问由谁来保证这个对象
  // 的资源释放呢？而且这新出现的异常又由谁来处理呢？不要忘记前面的一个异常目前
  // 都还没有处理结束，因此这就陷入了一个矛盾之中，或者说无限的递归嵌套之中。
}

void TestFooWithWrapperException() {
  try {
    FooWithWrapperException foo;
    foo.foo();
    foo.bar(); // 抛出异常
  } catch (runtime_error& e) {
    cerr << e.what() << endl;
  }
}

int main() {
  cout << "TestFoo:" << endl;
  TestFoo();
  cout << "TestFooWithException:" << endl;
  try {
    //TestFooWithException(); // 程序崩溃
  } catch (runtime_error& e) {
    // 并未catch住DestructorError
    cerr << e.what() << endl;
  }
  cout << "TestFooWithWrapperException:" << endl;
  TestFooWithWrapperException();
  return 0;
}
