// ValidSudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool check(char ch, bool used[9]) {
  if (ch == '.') {
    return true;
  }

  if (used[ch - '1']) {
    return false;
  }

  return used[ch - '1'] = true;
}

bool isValidSudoku(const vector<vector<char>>& board) {
  bool used[9];

  for (int i = 0; i < 9; i++) {
    fill(used, used + 9, false);

    for (int j = 0; j < 9; j++) {
            if (!check(board[i][j], used)
            {
        return false;
            }
    }

    for (int j = 0; j < 9; j++) {
            if (!check(board[j][i], used)
            {
        return false;
            }
    }
  }

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      fill(used, used + 9, false);

      for (int i = r * 3; i < r * 3 + 3; i++) {
        for (int j = c * 3; j < c * 3 + 3; j++) {
                    if (!check(board[i][j], used)
                    {
            return false;
                    }
        }
      }
    }
  }
  return true;
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
