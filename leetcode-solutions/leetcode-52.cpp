/*
N Queens

In this approach ,
Whenever a queen is placed, at first it is checked if it satisfies the conditions given that it is not under attack.

validMove function.
First it check there are no other queen in row the queen is filled.
As we are putting queen column wise so no need to check for column.
Then there are two diagonals to check for.

COLUMN_WISE FILLING = Only left part of the diagonals are checked as positions to the right of the present column are
still unfilled. ROW_WISE FILLING = Only upper part of the diagonals are checked as positions below of the present column
are still unfilled. If conditions satisfied, Queen is placed and we move to next column. If no queen satisfy the
problem, we backtrack and try to change the position of previous queen.
 */
#include <vector>
using namespace std;

bool isValid(vector<vector<int>> &board, int row, int col, int n) {
  for (int i = 0; i < n; ++i) {
    if (board[i][col] == 1) {
      return false;
    }
  }

  int x = row, y = col;
  while (x >= 0 && y >= 0) {
    if (board[x][y] == 1) {
      return false;
    }
    x--;
    y--;
  }

  x = row;
  y = col;
  while (x >= 0 && y < n) {
    if (board[x][y] == 1) {
      return false;
    }
    x--;
    y++;
  }
  return true;
}

int solveQueens(vector<vector<int>> &board, int n, int i) {
  if (i == n) {
    return 1;
  }

  int ways = 0;
  for (int j = 0; j < n; ++j) {
    if (!isValid(board, i, j, n)) {
      break;
    }

    board[i][j] = 1;
    ways += solveQueens(board, n, i + 1);
    board[i][j] = 0;
  }

  return ways;
}

int totalQueens(int n) {
  vector<vector<int>> board(n, vector<int>(n));
  return solveQueens(board, n, 0);
}