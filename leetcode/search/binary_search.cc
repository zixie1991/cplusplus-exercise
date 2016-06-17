#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int BinarySearch(const int* a, int n, int x) {
  int left = 0;
  int right = n - 1;
  int mid;
  while (left <= right) {
    mid = left + (right - left) / 2;
    //mid = (left + right) / 2;
    if (a[mid] == x) {
      return mid;
    } else if (x > a[mid]) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

int main() {
  return 0;
}
