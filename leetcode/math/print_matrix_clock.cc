#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

// 二维数组形参 int** == int*[]

void PrintMatrixInCircle(int** a, int rows, int cols, int start) {
  int end_row = rows - 1 - start;
  int end_col = cols - 1 - start;

  // left to right
  for (int j = start; j <= end_col; j++) {
    cout << a[start][j] << " ";
  }

  // top to bottom
  if (start < end_row) {
    for (int i = start + 1; i <= end_row; i++) {
      cout << a[i][end_col] << " ";
    }
  }

  // right to left
  if (start < end_row && start < end_col) {
    for (int j = end_col - 1; j >= start; j--) {
      cout << a[end_row][j] << " ";
    }
  }

  // bottom to top
  if (start < end_row - 1 && start < end_col) {
    for (int i = end_row - 1; i >= start + 1; i--) {
      cout << a[i][start] << " ";
    }
  }
}

// 顺时针打印二维数组
void PrintMatrixClock(int** a, int rows, int cols) {
  if (NULL == a || rows <= 0 || cols <= 0) {
    return ;
  }

  for (int start = 0; 2 * start < rows && 2 * start < cols; start++) {
    PrintMatrixInCircle(a, rows, cols, start);
  }
}

void TestPrintMatrixClock() {
  const int rows = 3;
  const int cols = 4;
  int a[][cols] = {{1, 2, 3, 4},
               {5, 6, 7, 8},
               {9, 10, 11, 12}};

  int* c[] = {a[0], a[1], a[2]};

  PrintMatrixClock(c, rows, cols);
}

int main() {
  cout << "TestPrintMatrixClock:" << endl;
  TestPrintMatrixClock();
  return 0;
}
