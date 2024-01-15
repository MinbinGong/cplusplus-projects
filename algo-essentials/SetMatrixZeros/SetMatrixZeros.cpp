// SetMatrixZeros.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

void setZeros1(vector<vector<int>>& matrix) {
  const size_t m = matrix.size();
  const size_t n = matrix[0].size();
  vector<bool> row(m, false);
  vector<bool> col(n, false);

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      if (matrix[i][j] == 0) {
        row[i] = col[j] = true;
      }
    }
  }

  for (size_t i = 0; i < m; i++) {
    if (row[i]) {
      fill(&matrix[i][0], &matrix[i][0] + n, 0);
    }
  }

  for (size_t j = 0; j < n; j++) {
    if (col[j]) {
      for (size_t i = 0; i < m; i++) {
        matrix[i][j] = 0;
      }
    }
  }
}

void setZeros2(vector<vector<int>>& matrix) {
  const size_t m = matrix.size();
  const size_t n = matrix[0].size();
  bool row_has_zero = false;
  bool col_has_zero = false;

  for (size_t i = 0; i < n; i++) {
    if (matrix[0][i] == 0) {
      row_has_zero = true;
      break;
    }
  }

  for (size_t i = 0; i < m; i++) {
    if (matrix[i][0] == 0) {
      col_has_zero = true;
      break;
    }
  }

  for (size_t i = 1; i < m; i++) {
    for (size_t j = 1; j < n; j++) {
      if (matrix[i][j] = 0) {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }

  for (size_t i = 1; i < m; i++) {
    for (size_t j = 1; j < n; j++) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0) {
        matrix[i][j] = 0;
      }
    }
  }

  if (row_has_zero) {
    for (size_t i = 0; i < n; i++) {
      matrix[0][i] = 0;
    }
  }

  if (col_has_zero) {
    for (size_t i = 0; i < m; i++) {
      matrix[i][0] = 0;
    }
  }
}

int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
