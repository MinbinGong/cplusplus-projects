/**
 * 1136. Parallel Courses
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * There are n courses, labeled from 1 to n. You are given an array relations where relations[i] = [xi, yi], representing a prerequisite relationship between course xi and course yi: course xi has to be taken before course yi.
 * 
 * In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous semester for the courses you are taking.
 * 
 * Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return -1.
 * 
 * Example 1:
 * Input: n = 3, relations = [[1,3],[2,3]]
 * Output: 2
 * Explanation: 
 * In the first semester, courses 1 and 2 are taken. In the second semester, course 3 is taken.
 * 
 * Example 2:
 * Input: n = 3, relations = [[1,2],[2,3],[3,1]]
 * Output: -1
 * Explanation: 
 * No course can be taken because they form a cycle.
 * 
 * Note:
 * 1 <= n <= 5000
 * 1 <= relations.length <= 5000
 * relations[i].length == 2
 * 1 <= xi, yi <= n
 * xi != yi
 * All the pairs [xi, yi] are unique.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        // 构建邻接表和入度数组
        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        for (auto& r : relations) {
            int prev = r[0], nxt = r[1];
            graph[prev].push_back(nxt);
            indegree[nxt]++;
        }
        
        // 队列中存放所有当前可学的课程（入度为0）
        queue<int> q;
        vector<int> depth(n + 1, 0);   // 记录每门课程需要的最少学期数
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                depth[i] = 1;          // 第一学期可学
            }
        }
        
        int visited = 0;
        int maxDepth = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            visited++;
            maxDepth = max(maxDepth, depth[cur]);
            
            for (int nxt : graph[cur]) {
                indegree[nxt]--;
                // 当前课程 cur 是 nxt 的先修，因此 nxt 的最早学期至少是 depth[cur] + 1
                depth[nxt] = max(depth[nxt], depth[cur] + 1);
                if (indegree[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }
        
        // 如果访问的课程数少于总课程数，说明存在环
        return visited == n ? maxDepth : -1;
    }
};