/*
Spiral Matrix

Given an m x n matrix, return all elements of the matrix in spiral order.

Approach:
1. Initialize four pointers: sr (start row), sc (start column), er (end row), and ec (end column).
2. Use a while loop to traverse the matrix in a spiral order.
3. Inside the loop, use four for loops to traverse the top, right, bottom, and left sides of the current sub-matrix.
4. Adjust the pointers accordingly after each traversal.
5. Continue until the entire matrix is traversed.
 */
#include <vector>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& mat) {
  if (mat.empty() || mat[0].empty()) {
    return {};
  }

  int sr = 0, sc = 0, er = mat.size() - 1, ec = mat[0].size() - 1, i;
  vector<int> v;
  while (sr <= er && sc <= ec) {
    for (i = sc; i <= ec && sr <= er; i++) {
      v.push_back(mat[sr][i]);
    }
    sr++;
    for (i = sr; i <= er && sc <= ec; i++) {
      v.push_back(mat[i][ec]);
    }
    ec--;
    for (i = ec; i >= sc && sr <= er; i--) {
      v.push_back(mat[er][i]);
    }
    er--;
    for (i = er; i >= sr && sc <= ec; i--) {
      v.push_back(mat[i][sc]);
    }
    sc++;
  }
  return v;
}