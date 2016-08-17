#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "timer.h"

using namespace std;
using namespace timer;

// FLOPS float-point operations per second
//


void TestFLOPS() {
  cout << "Test FLOPS:" << endl;
  const int num_flo = 1000000000;
  float a = 1.0;
  float b = 2.0;
  {
  AutoTimer timer(0, "a+b");
  for (int i = 0; i < num_flo; i++) {
    a + b;
  }
  }

  {
  AutoTimer timer(0, "a-b");
  for (int i = 0; i < num_flo; i++) {
    a + b;
  }
  }

  {
  AutoTimer timer(0, "a*b");
  for (int i = 0; i < num_flo; i++) {
    a * b;
  }
  }

  {
  AutoTimer timer(0, "a/b");
  for (int i = 0; i < num_flo; i++) {
    a * b;
  }
  }

}

void TestINTOPS() {
  cout << "Test INTOPS:" << endl;
  const int num_flo = 1000000000;
  int a = 1;
  int b = 2;
  {
  AutoTimer timer(0, "a+b");
  for (int i = 0; i < num_flo; i++) {
    a + b;
  }
  }

  {
  AutoTimer timer(0, "a-b");
  for (int i = 0; i < num_flo; i++) {
    a + b;
  }
  }

  {
  AutoTimer timer(0, "a*b");
  for (int i = 0; i < num_flo; i++) {
    a * b;
  }
  }

  {
  AutoTimer timer(0, "a/b");
  for (int i = 0; i < num_flo; i++) {
    a * b;
  }
  }

}

int main() {
  TestFLOPS();
  TestINTOPS();
  return 0;
}
