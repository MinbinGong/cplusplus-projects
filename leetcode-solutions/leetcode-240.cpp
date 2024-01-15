/*
Search a 2D matrix

题目描述
给定一个二维矩阵，已知每行和每列都是增序的，尝试设计一个快速搜索一个数字是否在矩
阵中存在的算法。

题解
这道题有一个简单的技巧：我们可以从右上角开始查找，若当前值大于待搜索值，我们向左
移动一位；若当前值小于待搜索值，我们向下移动一位。如果最终移动到左下角时仍不等于待搜
索值，则说明待搜索值不存在于矩阵中。
 */
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
  if (matrix.size() == 0) {
    return false;
  }

  int m = matrix.size();
  int n = matrix[0].size();
  int i = 0, j = n - i;
  while (i < m && j >= 0) {
    if (matrix[i][j] == target) {
      return true;
    } else if (matrix[i][j] > target) {
      --j;
    } else {
      ++i;
    }
  }
  return false;
}