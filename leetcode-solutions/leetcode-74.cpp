/*
Search a 2D matrix

You are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous row.
Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

 */
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>> &v, int target) {
  int m = v.size(), n = v[0].size();
  int start = 0, end = m * n - 1;

  while (start <= end) {
    int mid = start + (end - start) / 2;
    int row = mid / v[0].size(), col = mid % v[0].size();
    if (v[row][col] == target) {
      return true;
    }

    if (v[row][col] < target) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return false;
}