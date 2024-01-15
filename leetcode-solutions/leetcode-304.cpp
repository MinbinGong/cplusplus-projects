/*
Range sum query 2D - immutable

题目描述
设计一个数据结构，使得其能够快速查询给定矩阵中，任意两个位置包围的长方形中所有数
字的和。

题解
类似于前缀和，我们可以把这种思想拓展到二维，即积分图（image integral）
。我们可以先建
立一个 intergral 矩阵，intergral[i][j] 表示以位置 (0, 0) 为左上角、位置 (i, j) 为右下角的长方形中
所有数字的和。
 */
#include <vector>
using namespace std;

class NumMatrix {
  vector<vector<int>> integral;

 public:
  NumMatrix(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = m > 0 ? matrix[0].size() : 0;
    integral = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
      for (int j = 0; j <= n; ++j) {
        integral[i][j] = matrix[i - 1][j - 1] + integral[i - 1][j] + integral[i][j - 1] - integral[i - 1][j - 1];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return integral[row2 + 1][col2 + 1] - integral[row2 + 1][col1] - integral[row1][col2 + 1] + integral[row1][col1];
  }
};