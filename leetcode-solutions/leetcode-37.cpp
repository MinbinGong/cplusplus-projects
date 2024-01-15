/*
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * A sudoku solution must satisfy all of the following rules:
 *
 *  Each of the digits 1-9 must occur exactly once in each row.
 *  Each of the digits 1-9 must occur exactly once in each column.
 *  Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 *
 * The '.' character indicates empty cells.
 */
#include <vector>

void ans(std::vector<std::vector<char>>& board, std::vector<std::vector<char>>& curr, int i, int j,
         std::vector<std::vector<bool>>& col, std::vector<std::vector<bool>>& row,
         std::vector<std::vector<bool>>& mat) {
  while (i < 9 && board[i][j] != '.') {
    if (j < 8) {
      j++;
    } else {
      j = 0;
      i++;
    }
  }

  if (i == 0) {
    curr = board;
    return;
  }

  for (int k = 1; k <= 9; k++) {
    if (curr.size() > 0) break;
    if (!col[j][k] && !row[i][k] && !mat[3 * (i / 3) + (j / 3)][k]) {
      col[j][k] = true;
      row[i][k] = true;
      mat[3 * (i / 3) + (j / 3)][k] = true;
      board[i][j] = (char)('0' + k);
      ans(board, curr, i, j, col, row, mat);
      col[j][k] = false;
      row[i][k] = false;
      mat[3 * (i / 3) + (j / 3)][k] = false;
      board[i][j] = '.';
    }
  }
}

void solveSudoku(std::vector<std::vector<char>>& board) {
  std::vector<std::vector<bool>> col(9, std::vector<boo>(10, false));
  std::vector<std::vector<bool>> row(9, std::vector<boo>(10, false));
  std::vector<std::vector<bool>> mat(9, std::vector<boo>(10, false));
  std::vector<std::vector<char>> curr;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == '.') {
        continue;
      }

      int x = board[i][j] - '0';
      row[i][x] = true;
      col[j][x] = true;
      mat[3 * (i / 3) + (j / 3)][x] = true;
    }
  }

  ans(board, curr, 0, 0, col, row, mat);
  board = curr;
  return;
}
