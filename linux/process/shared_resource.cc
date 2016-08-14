#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int g_a = 1;

int main() {
  int *b = new int[2];
  b[0] = 1;
  b[1] = 2;

  pid_t pid;

  if ((pid = fork()) < 0) {
    fprintf(stderr, "fork error %s\n", strerror(errno));
    return 0;
  } else if (pid == 0) {
    pid = getpid();
    printf("%d %p %p\n", pid, &g_a, b);
    g_a = 2;
    b[0] = 8;
    b[1] = 9;
    cout << pid << " " << g_a << endl;
    cout << pid << " " << b[0] << " " << b[1] << endl;

    if (b) {
      delete[] b;
      b = NULL;
    }
  } else {
    sleep(1);
    pid = getpid();
    printf("%d %p %p\n", pid, &g_a, b);
    cout << pid << " " << g_a << endl;
    cout << pid << " " << b[0] << " " << b[1] << endl;
  }

  wait(NULL);

  return 0;
}
