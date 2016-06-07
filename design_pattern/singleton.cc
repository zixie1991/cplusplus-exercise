#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

// Disable the copy and assignment operator for a class.
#define DISABLE_COPY_AND_ASSIGN(classname) \
private:\
  classname(const classname&);\
  classname& operator=(const classname&)

// 单例模式
// C++ 线程安全的单例模式: http://www.cnblogs.com/ccdev/archive/2012/12/19/2825355.html
// 单例模式(Singleton)及其C++实现: http://www.zkt.name/dan-li-mo-shi-singleton-ji-c-shi-xian/

class Singleton {
  public:
    Singleton() {}
    virtual ~Singleton() {}
    //virtual static Singleton& instance() {} // cannot be declared both virtual and static
};

/**
 * @brief 饿汉模式
 */
class EagerSingleton {
  public:
    static EagerSingleton& instance() {
      return *instance_;
    }

  private:
    EagerSingleton() {}
    DISABLE_COPY_AND_ASSIGN(EagerSingleton);
    static EagerSingleton* instance_;
};

EagerSingleton* EagerSingleton::instance_ = new EagerSingleton();

/**
 * @brief 懒汉模式(静态成员变量)
 */
class LazySingleton {
  public:
    static LazySingleton& instance() {
      if (instance_ == NULL) {
        instance_ = new LazySingleton();
      }

      return *instance_;
    }

  private:
    LazySingleton() {}
    DISABLE_COPY_AND_ASSIGN(LazySingleton);
    static LazySingleton* instance_;
};

LazySingleton* LazySingleton::instance_ = NULL;

/**
 * @brief 懒汉模式(模本+静态成员变量)
 */
template <typename T>
class LazySingletonTemplate {
  public:
    static T& instance() {
      if (instance_ == NULL) {
        instance_ = new T();
      }

      return *instance_;
    }

  private:
    LazySingletonTemplate() {}
    DISABLE_COPY_AND_ASSIGN(LazySingletonTemplate);

    static T* instance_;
};

template <typename T>
T* LazySingletonTemplate<T>::instance_ = NULL;

class LazySingletonTemplateType {
  private:
    friend class LazySingletonTemplate<LazySingletonTemplateType>;
    LazySingletonTemplateType() {}
};

/**
 * @brief 懒汉模式(静态局部变量)
 */
class LazySingletonInside {
  public:
    static LazySingletonInside& instance() {
      // after c++0x, it's thread safe
      static LazySingletonInside in;
      return in;
    }

  private:
    LazySingletonInside() {}
    DISABLE_COPY_AND_ASSIGN(LazySingletonInside);
};

/**
 * @brief 懒汉模式(线程安全, 双重检验锁)
 */
class LazySingletonSafe {
  public:
    static LazySingletonSafe& instance() {
      if (instance_ == NULL) {
        // lock
        if (instance_ == NULL) {
          instance_ = new LazySingletonSafe();
        }
        // unlock
      }
    }

  private:
    LazySingletonSafe() {}
    DISABLE_COPY_AND_ASSIGN(LazySingletonSafe);
    static LazySingletonSafe* instance_;
};

LazySingletonSafe* LazySingletonSafe::instance_ = NULL;

/**
 * @brief 懒汉模式(线程安全, pthread_once)
 */
class LazySingletonSafe2 {
  public:
    static LazySingletonSafe2& instance() {
      pthread_once(&init_flag_, Init);

      return *instance_;
    }

  private:
    LazySingletonSafe2() {}
    DISABLE_COPY_AND_ASSIGN(LazySingletonSafe2);

    static void Init() {
      instance_ = new LazySingletonSafe2();
    }

    // man pthread_once
    // linux默认没有安装posix的手册, 需要自己手动安装 apt-get install manpages-posix-dev
    static pthread_once_t init_flag_;
    static LazySingletonSafe2* instance_;
};

pthread_once_t LazySingletonSafe2::init_flag_ = PTHREAD_ONCE_INIT;
LazySingletonSafe2* LazySingletonSafe2::instance_ = NULL;

int main() {
  EagerSingleton& eager_singleton = EagerSingleton::instance();
  LazySingleton& lazy_singleton = LazySingleton::instance();
  LazySingletonTemplateType& lazy_singleton_template_type = LazySingletonTemplate<LazySingletonTemplateType>::instance();
  LazySingletonInside& lazy_singleton_inside = LazySingletonInside::instance();
  LazySingletonSafe& lazy_singleton_safe = LazySingletonSafe::instance();
  LazySingletonSafe2& lazy_singleton_safe2 = LazySingletonSafe2::instance();

  return 0;
}
