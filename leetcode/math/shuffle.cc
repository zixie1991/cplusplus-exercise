#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 洗牌算法
// Python和C++中洗牌算法Shuffle的实现: http://codeup.org/archives/439

class Rand {
  public:
    static Rand* instance() {
      static Rand rand_;
      return &rand_;
    }

    int Get() {
      return random();
    }

    int Get(int begin, int end) {
      int dist = end - begin;
      return Get() % dist + begin;
    }

  private:
    Rand() {
      srand(time(0));
    }
};

void Shuffe(int* a, int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = Rand::instance()->Get(0, i);
    
    // swap
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
}

void TestShuffle() {
  cout << "TestShuffle:" << endl;
  int a[] = {1, 2, 3, 4, 5, 6};
  const int n = 6;

  Shuffe(a, n);
  
  for (int i = 0; i < n; i ++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  TestShuffle();
  return 0;
}
