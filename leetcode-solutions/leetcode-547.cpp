/*
    题目描述
        给定一个二维的 0-1 矩阵，如果第 (i, j) 位置是 1，则表示第 i 个人和第 j 个人是朋友。已知
    朋友关系是可以传递的，即如果 a 是 b 的朋友，b 是 c 的朋友，那么 a 和 c 也是朋友，换言之这
    三个人处于同一个朋友圈之内。求一共有多少个朋友圈。

    题解
        对于题目 695，图的表示方法是，每个位置代表一个节点，每个节点与上下左右四个节点相
    邻。而在这一道题里面，每一行（列）表示一个节点，它的每列（行）表示是否存在一个相邻节
    点。因此题目 695 拥有 m × n 个节点，每个节点有 4 条边；而本题拥有 n 个节点，每个节点最多
    有 n 条边，表示和所有人都是朋友，最少可以有 1 条边，表示自己与自己相连。当清楚了图的表
    示方法后，这道题与题目 695 本质上是同一道题：搜索朋友圈（岛屿）的个数（最大面积）。我
    们这里采用递归的第一种写法。
 */
#include <vector>
using namespace std;

void dfs(vector<vector<int>>& friends, int i, vector<bool>& visited) {
  visited[i] = true;
  for (int k = 0; k < friends.size(); ++k) {
    if (friends[i][k] == 1 && !visited[k]) {
      dfs(friends, k, visited);
    }
  }
}

int findCircleNum(vector<vector<int>>& friends) {
  int n = friends.size();
  int count = 0;
  vector<bool> visited(n, false);
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(friends, i, visited);
      ++count;
    }
  }
  return count;
}