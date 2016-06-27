#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include <iostream>

using namespace std;

// 动态调用动态库方法 c/c++ linux/Oceanix: http://m.blog.chinaunix.net/uid-29354464-id-5108404.html

typedef void (*func_t)();

int main(int argc, char* argv[]) {
  
  const char* dlpath = argv[1];
  const char* func_name = argv[2];
  const char* error = NULL;

  void* handle = dlopen(dlpath, RTLD_NOW);
  if (NULL != (error = dlerror())) {
    fprintf(stderr, "dlopen error %s\n", error);
    return -1;
  }

  func_t func = (func_t)dlsym(handle, func_name);
  if (NULL != (error = dlerror())) {
    fprintf(stderr, "dlsym error %s\n", error);
    return -1;
  }

  func();

  dlclose(handle);
  if (NULL != (error = dlerror())) {
    fprintf(stderr, "dlclose error %s\n", error);
    return -1;
  }

  return 0;
}
