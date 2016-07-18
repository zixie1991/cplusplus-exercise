#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include <string>

using std::string;

namespace timer {

static inline long GetMicros() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return static_cast<long>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

static inline int32_t NowTime() {
  return static_cast<int32_t>(GetMicros() / 1000000);
}

static inline int32_t NowTimeStr(char* buf, int32_t len) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  const time_t seconds = tv.tv_sec;
  struct tm t;
  localtime_r(&seconds, &t);
  return snprintf(buf, len, "%02d/%02d %02d:%02d:%02d.%06d",
                  t.tm_mon + 1,
                  t.tm_mday,
                  t.tm_hour,
                  t.tm_min,
                  t.tm_sec,
                  static_cast<int>(tv.tv_usec));
}


class AutoTimer {
  public:
    AutoTimer(const string& str=""):
      str_(str) 
    {
      start_ = GetMicros();
    }

    ~AutoTimer() {
      long end = GetMicros();
      double t = (end - start_) / 1000.0;
      fprintf(stderr, "%s use %.3f ms\n", str_.c_str(), t);
    }

  private:
    long start_;
    string str_;
};

}

#endif
