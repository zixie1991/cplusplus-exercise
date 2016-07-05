#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <list>

using namespace std;

// 观察者模式
// C++设计模式——观察者模式: http://www.jellythink.com/archives/359
// 我所理解的设计模式（C++实现）——观察者模式（Observer Pattern）: http://blog.csdn.net/lcl_data/article/details/9208561

class Observer;

// 被观察者
class Subject {
  public:
    virtual ~Subject() {}

    virtual void Attach(Observer* observer) = 0;
    virtual void Detach(Observer* observer) = 0;
    virtual void Notify() = 0;
};

// 观察者
class Observer {
  public:
    virtual ~Observer() {}
    virtual void Update() = 0;
};

class ConcreteSubject: public Subject {
  public:
    ConcreteSubject() {}
    ~ConcreteSubject() {}

    void Attach(Observer* observer) {
      observers_.push_back(observer);
    }
    
    void Detach(Observer* observer) {
      observers_.remove(observer);
    }

    void Notify() {
      for (list<Observer*>::const_iterator iter = observers_.begin(); iter != observers_.end(); ++iter) {
        (*iter)->Update();
      }
    }

  private:
    list<Observer*> observers_;
};

class ConcreteObserver: public Observer {
  public:
    ConcreteObserver() {}
    ~ConcreteObserver() {}

    void Update() {
      cout << "Update()" << endl;
    }
};

int main() {
  Subject* subject = new ConcreteSubject();
  Observer* observer1 = new ConcreteObserver();
  Observer* observer2 = new ConcreteObserver();
  Observer* observer3 = new ConcreteObserver();

  subject->Attach(observer1);
  subject->Attach(observer2);
  subject->Attach(observer3);

  subject->Notify();

  subject->Detach(observer3);

  subject->Notify();

  return 0;
}
