#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// template中的typename和class并没有任何差别

template <typename C>
void PrintIter2(const C& container) {
  typename C::const_iterator x; // typename标识嵌套从属类型名称
  x = container.begin();
  ++x;
  cout << *x << endl;
}

template<typename T>
class Base {
  public:
    class Nested {
      public:
        Nested(int x) {}
        void Foo() {
          cout << "Nested::Foo()" << endl;
        }
    };
};

template <typename T>
class Derived: public Base<T>::Nested { // 继承父类不需要也不能使用typename标识嵌套从属类型名称
  public:
    Derived(int x):
      Base<T>::Nested(x) // 初始化成员列表不需要也不能使用typename标识嵌套从属类型名称
    {
      typename Base<T>::Nested t(x); // typename 标识嵌套从属类型名称
      t.Foo();
    }
};

int main() {
  Derived<int> d(1);
  return 0;
}
