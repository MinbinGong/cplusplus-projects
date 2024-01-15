/*
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
 * validated according to the following rules:
 *      Each row must contain the digits 1-9 without repetition.
 *      Each column must contain the digits 1-9 without repetition.
 *      Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9
 *      without repetition.
 *
 * Note: A Sudoku board (partially filled) could be valid but is not necessarily
 * solvable. Only the filled cells need to be validated according to the
 * mentioned rules.
 */
#include <set>
#include <vector>

bool isValidSudoku(std::vector<std::vector<char>>& board) {
  std::set<int> foundx, foundy;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (foundx.find(board[i][j] - '0') != foundx.end()) {
        return false;
      } else if (board[i][j] != '.') {
        foundx.insert(board[i][j] - '0');
      }

      if (foundy.find(board[j][i] - '0') != foundy.end()) {
        return false;
      } else if (board[j][i] != '.') {
        foundy.insert(board[j][i] - '0');
      }
    }
    foundx.clear();
    foundy.clear();
  }

  foundx.clear();

  std::vector<std::vector<int>> boxes = {{0, 0}, {0, 3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {6, 0}, {6, 3}, {6, 6}};

  for (auto b : boxes) {
    for (int i = b[0]; i < b[0] + 3; i++) {
      for (int j = b[1]; j < b[1] + 3; j++) {
        if (foundx.find(board[i][j] - '0') != foundx.end()) {
          return false;
        } else if (board[i][j] != '.') {
          foundx.insert(board[i][j] - '0');
        }
      }
    }
    foundx.clear();
  }
  return true;
}
