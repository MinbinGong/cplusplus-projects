/*
  Surrounded Regions

  Given an m x n matrix board containing 'X' and 'O',
  capture all regions that are 4-directionally surrounded by 'X'.

  A region is captured by flipping all 'O's into 'X's in that surrounded region.
 */
#include <vector>
#include <queue>
using namespace std;

void bfs(vector<vector<char>>& board, int x, int y) {
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};

}