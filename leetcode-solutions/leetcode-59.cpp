/*
Spiral Matrix II

Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.

 */
#include <vector>
using namespace std;

vector<vector<int>> generateMatrix(int n) {
  vector<vector<int>> arr(n, vector<int>(n, 0));
  int i = 0, j = 0, k = 1;
  while (k <= n * n) {
    // go left to right
    j = i;
    while (j < n - i) {
      arr[i][j++] = k++;
    }

    // go top to down
    j = i + 1;
    while (j < n - i) {
      arr[j++][n - i - 1] = k++;
    }

    // go right to left
    j = n - i - 2;
    while (j > i) {
      arr[n - i - 1][j--] = k++;
    }

    // go bottom to up
    j = n - i - 1;
    while ((j > i)) {
      arr[j--][i] = k++;
    }

    i++;
  }

  return arr;
}