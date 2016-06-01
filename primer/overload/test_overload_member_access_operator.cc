#include <iostream>

using namespace std;

class Base {
  public:
    Base(int n):
      n_(n)
    {}

    int n_;
};

class WrapperBase {
  public:
    WrapperBase(Base* base):
      base_(base)
    {}

    Base* operator->() {
      return base_;
    }

  private:
    Base* base_;
};

class WrapperWrapperBase {
  public:
    WrapperWrapperBase(WrapperBase* wrapper_base):
      wrapper_base_(wrapper_base)
    {}

    WrapperBase& operator->() {
      return *wrapper_base_;
    }

  private:
    WrapperBase* wrapper_base_;
};

class Wrapper2WrapperBase {
  public:
    Wrapper2WrapperBase(WrapperBase* wrapper_base):
      wrapper_base_(wrapper_base)
    {}

    WrapperBase* operator->() {
      return wrapper_base_;
    }

  private:
    WrapperBase* wrapper_base_;
};

int main() {
  Base base(8);
  WrapperBase wrapper_base(&base);
  WrapperWrapperBase wrapper_wrapper_base(&wrapper_base);
  Wrapper2WrapperBase wrapper2_wrapper_base(&wrapper_base);

  cout << "&base=" << &base << endl;
  cout << "&base->n_=" << &base.n_ << endl;
  cout << "&wrapper_base=" << &wrapper_base << endl;
  cout << "&wrapper_wrapper_base=" << &wrapper_wrapper_base << endl;
  cout << "&wrapper2_wrapper_base=" << &wrapper2_wrapper_base << endl;

  cout << "wrapper_base.operator->()=" << wrapper_base.operator->() << endl;
  cout << "&wrapper_wrapper_base.operator->()=" << &wrapper_wrapper_base.operator->() << endl;
  cout << "wrapper_wrapper_base.operator->().operator->()=" << wrapper_wrapper_base.operator->().operator->() << endl;
  cout << "wrapper2_wrapper_base.operator->()=" << wrapper2_wrapper_base.operator->() << endl;
  cout << "wrapper_base->n_=" << wrapper_base->n_ << endl;
  cout << "&wrapper_base->n_=" << &wrapper_base->n_ << endl;
  cout << "wrapper_wrapper_base->n_=" << wrapper_wrapper_base->n_ << endl;
  cout << "&wrapper_wrapper_base->n_=" << &wrapper_wrapper_base->n_ << endl;

  return 0;
}
