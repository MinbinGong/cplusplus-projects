/*
Is Graph Bipartite

题目描述
给定一个图，判断其是否可以二分，

题解
利用队列和广度优先搜索，我们可以对未染色的节点进行染色，并且检查是否有颜色相同的
相邻节点存在。注意在代码中，我们用 0 表示未检查的节点，用 1 和 2 表示两种不同的颜色。
 */
#include <queue>
#include <vector>
using namespace std;

bool isBipartite(vector<vector<int>>& graph) {
  if (graph.empty()) {
    return true;
  }

  int n = graph.size();
  vector<int> color(n, 0);
  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (color[i] == 0) {
      q.push(i);
      color[i] = 1;
    }

    while (!q.empty()) {
      int node = q.front();
      q.pop();
      for (const auto& j : graph[node]) {
        if (color[j] == 0) {
          q.push(j);
          color[j] = color[node] == 2 ? 1 : 2;
        } else if (color[node] == color[j]) {
          return false;
        }
      }
    }
  }
  return true;
}