/*
 * Course Schedule
 *
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array
 * prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take
 * course ai.
 *
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 *
 * Return true if you can finish all courses. Otherwise, return false.
 *
 * Constraints:
 * 1. 1 <= numCourses <= 2000
 * 2. 0 <= prerequisites.length <= 5000
 * 3. prerequisites[i].length == 2
 * 4. 0 <= ai, bi < numCourses
 * 5. All the pairs prerequisites[i] are unique.
 * 6. prerequisites[i] != prerequisites[j] for i != j.
 */
#include <queue>
#include <vector>
#include <functional>
using namespace std;

bool canFinishWithBFS(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> graph(numCourses);
  vector<int> indegree(numCourses, 0);

  // Build graph and compute indegree
  for (const auto& pre : prerequisites) {
    int course = pre[0];
    int prereq = pre[1];
    graph[prereq].push_back(course);
    indegree[course]++;
  }

  queue<int> q;
  // Add all nodes with indegree 0 to queue
  for (int i = 0; i < numCourses; ++i) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  int processed = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    processed++;
    for (int v : graph[u]) {
      indegree[v]--;
      if (indegree[v] == 0) {
        q.push(v);
      }
    }
  }

  return processed == numCourses;
}

bool canFinishWithDFS(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> graph(numCourses);
  for (const auto& pre : prerequisites) {
    graph[pre[1]].push_back(pre[0]);  // prereq -> course
  }

  vector<int> state(numCourses, 0);  // 0=unvisited, 1=visiting, 2=visited

  function<bool(int)> dfs = [&](int u) -> bool {
    if (state[u] == 1) return true;   // cycle detected
    if (state[u] == 2) return false;  // already processed

    state[u] = 1;  // mark as visiting
    for (int v : graph[u]) {
      if (dfs(v)) return true;
    }
    state[u] = 2;  // mark as visited
    return false;
  };

  for (int i = 0; i < numCourses; ++i) {
    if (state[i] == 0) {
      if (dfs(i)) return false;  // cycle found
    }
  }
  return true;
}