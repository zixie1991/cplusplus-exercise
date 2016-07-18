#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <stdexcept>

using namespace std;

// 函数指针
typedef void(*NewHandler)();

void Foo() {
  cout << "Foo" << endl;
  // 卸载new_handler
  set_new_handler(NULL);
}

void Bar() {
  cout << "Bar" << endl;
  set_new_handler(NULL);
}

class NewHandlerHolder {
  public:
    NewHandlerHolder(new_handler handler):
      handler_(handler)
    {
      // 获取一笔资源
    }

    ~NewHandlerHolder() {
      // 归还资源
      set_new_handler(handler_);
    }
    
  private:
    new_handler handler_;
};

// 类专属的new_handler
class NewHandlerSupport {
  public:
    static new_handler set_new_handler(new_handler handler);
    static void* operator new(size_t size) throw (bad_alloc);
    static void* operator new[] (size_t size) throw (bad_alloc);
    static void* operator new[] (size_t size, const nothrow_t& nothrow_value) throw ();

  private:
    static new_handler current_handler_;
};

new_handler NewHandlerSupport::current_handler_ = NULL;

new_handler NewHandlerSupport::set_new_handler(new_handler handler) {
  new_handler old_handler = current_handler_;
  current_handler_ = handler;

  return old_handler;
}

void* NewHandlerSupport::operator new(size_t size) throw (bad_alloc) {
  NewHandlerHolder new_handler_holder(std::set_new_handler(current_handler_));
  return ::operator new(size);
}

void* NewHandlerSupport::operator new[] (size_t size) throw (bad_alloc) {
  NewHandlerHolder new_handler_holder(std::set_new_handler(current_handler_));
  return ::operator new[](size);
}

void* NewHandlerSupport::operator new[] (size_t size, const nothrow_t& nothrow_value) throw () {
  NewHandlerHolder new_handler_holder(std::set_new_handler(current_handler_));
  return ::operator new[](size);
}

class A {
};

void TestNewHandler() {
  cout << "TestNewHandler:" << endl;
  NewHandler handler = Foo;
  handler();

  set_new_handler(Bar);
  // 分配内存失败时，不断调用Foo, 直至找到足够的内存
  handler = set_new_handler(Foo);
  handler();
  // 内存分配失败返回NULL, 并不抛出异常
  int* a = new (nothrow)int[-1];
}

void TestNewHandlerHolder() {
  cout << "TestNewHandlerHolder:" << endl;
  set_new_handler(Foo);
  {
  NewHandlerHolder new_handler_holder(set_new_handler(NULL));
  int* a = new (nothrow)int[-1];
  }
  cout << "分割线" << endl;
  int*b = new (nothrow)int[-1];
}

void TestNewHandlerSupport() {
  cout << "TestNewHandlerSupport:" << endl;
  set_new_handler(Bar);
  NewHandlerSupport::set_new_handler(Foo);
  try {
    NewHandlerSupport* s1 = new NewHandlerSupport[-1];
  } catch (...) {
  }
  cout << "分割线" << endl;
  A* a = new (nothrow)A[-1];
}

int main() {
  TestNewHandler();
  TestNewHandlerHolder();
  TestNewHandlerSupport();
  return 0;
}
