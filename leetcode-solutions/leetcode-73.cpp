/*
Set Matrix Zeroes

Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

 */
#include <unordered_set>
#include <vector>
using namespace std;

void setZeros(vector<vector<int>>& matrix) {
  vector<pair<int, int>> temp;
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      if (matrix[i][j] == 0) {
        temp.push_back(make_pair(i, j));
      }
    }
  }

  for (int i = 0; i < temp.size; ++i) {
    int row = temp[i].first, col = temp[i].second;
    for (int j = 0; j < matrix.size(); ++j) {
      for (int k = 0; k < matrix[j].size(); k++) {
        if (j == row) {
          matrix[j][k] = 0;
        }
        if (k == col) {
          matrix[j][k] = 0;
        }
      }
    }
  }
}

void setZeros1(vector<vector<int>>& matrix) {
  int m = matrix.size(), n = matrix[0].size();
  unordered_set<int> setRows;
  unordered_set<int> setCols;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == 0) {
        setRows.insert(i);
        setCols.insert(j);
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (setRows.count(i) > 0 || setCols.count(j) > 0) {
        matrix[i][j] = 0;
      }
    }
  }
}