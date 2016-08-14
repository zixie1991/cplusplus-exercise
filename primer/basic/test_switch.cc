#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

enum Mode{kNew=-1, kRead, kWrite};

void TestSwitchCaseType() {
  // type require integer
  float f;
  switch (static_cast<int>(f)) {
    case int(1.0):
    case int(2.0):
      break;
  }

  enum Mode mode;
  switch (mode) {
    case kNew:
    case kRead:
    case kWrite:
      break;
  }
}

int main() {
  cout << (int)'a' << " " << (int)'A' << " " << (int)'0' << endl;
  return 0;
}
