// RotateImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void rotate1(vector<vector<int>>& matrix) {
  const int n = matrix.size();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i; j++) {
      swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
    }
  }

  for (int i = 0; i < n / 2; i++) {
    for (int j = 0; j < n; j++) {
      swap(matrix[i][j], matrix[n - 1 - i][j]);
    }
  }
}

void rotate2(vector<vector<int>>& matrix) {
  const int n = matrix.size();

  for (int i = 0; i < n / 2; i++) {
    for (int j = 0; j < n; j++) {
      swap(matrix[i][j], matrix[n - 1 - i][j]);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      swap(matrix[i][j], matrix[j][i]);
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
