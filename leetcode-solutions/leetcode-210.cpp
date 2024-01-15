/*
Course schedule

题目描述
给定 N 个课程和这些课程的前置必修课，求可以一次性上完所有课的顺序。

题解
我们可以先建立一个邻接矩阵表示图，方便进行直接查找。这里注意我们将所有的边反向，使得如果课程 i 指向课程 j，那么课程 i
需要在课程 j 前面先修完。这样更符合我们的直观理解。
拓扑排序也可以被看成是广度优先搜索的一种情况：我们先遍历一遍所有节点，把入度为 0
的节点（即没有前置课程要求）放在队列中。在每次从队列中获得节点时，我们将该节点放在目
前排序的末尾，并且把它指向的课程的入度各减 1；如果在这个过程中有课程的所有前置必修课都已修完（即入度为 0）
，我们把这个节点加入队列中。当队列的节点都被处理完时，说明所有的节点都已排好序，或因图中存在循环而无法上完所有课程。
 */
#include <queue>
#include <vector>
using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> graph(numCourses, vector<int>());
  vector<int> indegree(numCourses, 0), res;

  for (const auto& prerequisite : prerequisites) {
    graph[prerequisite[1]].push_back(prerequisite[0]);
    ++indegree[prerequisite[0]];
  }

  queue<int> q;
  for (int i = 0; i < indegree.size(); ++i) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    res.push_back(u);
    q.pop();

    for (auto v : graph[u]) {
      --indegree[v];
      if (indegree[v] == 0) {
        q.push(v);
      }
    }
  }

  for (int i = 0; i < indegree.size(); ++i) {
    if (indegree[i]) {
      return vector<int>();
    }
  }
  return res;
}