/*
 * Course schedule II
 * 
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
 * 
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 * Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
 * 
 * Constraints:
 * 1. 1 <= numCourses <= 2000
 * 2. 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 * 3. prerequisites[i].length == 2
 * 4. 0 <= ai, bi < numCourses
 * 5. ai != bi
 * 6. All the pairs [ai, bi] are distinct.
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