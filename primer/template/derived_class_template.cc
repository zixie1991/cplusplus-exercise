#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class CompanyA {
  public:
    void send() {
    }
};

class CompanyB {
  public:
    void send() {
    }
};

class CompanyC {
  public:
    void send2() {
    }
};

template <typename Company>
class MsgSender {
  public:
    void send() {
      Company c;
      c.send();
    }
};

// 类模板MsgSender特化
template <>
class MsgSender<CompanyC> {
  public:
    void send2() {
      CompanyC c;
      c.send2();
    }
};

template <typename Company>
class LoggingMsgSender: public MsgSender<Company> {
  public:
    using MsgSender<Company>::send;

    void sendMsg() {
      send(); // combine with using

      //this->send();

      //MsgSender<Company>::send();

      //send(); //  error
    }
};

int main() {
  return 0;
}
