/*
    题目描述
        给定一个字母矩阵，所有的字母都与上下左右四个方向上的字母相连。给定一个字符串，求
    字符串能不能在字母矩阵中寻找到。

    题解
        不同于排列组合问题，本题采用的并不是修改输出方式，而是修改访问标记。在我们对任意
    位置进行深度优先搜索时，我们先标记当前位置为已访问，以避免重复遍历（如防止向右搜索后
    又向左返回）；在所有的可能都搜索完成后，再回改当前位置为未访问，防止干扰其它位置搜索
    到当前位置。使用回溯法，我们可以只对一个二维的访问矩阵进行修改，而不用把每次的搜索状
    态作为一个新对象传入递归函数中。
 */
#include <string>
#include <vector>
using namespace std;

void backtracking(int i, int j, vector<vector<char>> &board, string &word, bool &find, vector<vector<bool>> &visited,
                  int pos) {
  if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
    return;
  }

  if (visited[i][j] || find || board[i][j] != word[pos]) {
    return;
  }
  if (pos == word.size() - 1) {
    find = true;
    return;
  }
  visited[i][j] = true;
  backtracking(i + 1, j, board, word, find, visited, pos + 1);
  backtracking(i - 1, j, board, word, find, visited, pos + 1);
  backtracking(i, j + 1, board, word, find, visited, pos + 1);
  backtracking(i, j - 1, board, word, find, visited, pos + 1);
  visited[i][j] = false;
}

bool exit(vector<vector<char>> &board, string word) {
  if (board.empty()) {
    return false;
  }

  int m = board.size(), n = board[0].size();
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  bool find = false;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      backtracking(i, j, board, word, find, visited, 0);
    }
  }
  return find;
}