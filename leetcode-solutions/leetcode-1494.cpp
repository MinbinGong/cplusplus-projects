/**
 * 1494. Parallel Courses II
 * 
 * Given the integer n, which is the number of courses numbered from 1 to n, and the array dependencies where dependencies[i] = [xi, yi]  represents a prerequisite relationship, that is, the course xi must be taken before the course yi.  Also, you are given the integer k.
 * 
 * In one semester you can take at most k courses as long as you have taken all the prerequisites for the courses you are taking.
 * 
 * Return the minimum number of semesters to take all courses. It is guaranteed that you can take all courses in some way.
 * 
 * Example 1:
 * Input: n = 4, dependencies = [[2,1],[3,1],[1,4]], k = 2
 * Output: 3 
 * Explanation: The figure above represents the given graph. In this case we can take courses 2 and 3 in the first semester, then take course 1 in the second semester and finally take course 4 in the third semester.
 * 
 * Example 2:
 * Input: n = 5, dependencies = [[2,1],[3,1],[4,1],[1,5]], k = 2
 * Output: 4 
 * Explanation: The figure above represents the given graph. In this case one optimal way to take all courses is: take courses 2 and 3 in the first semester, then take course 4 in the second semester, then take courses 1 and 5 in the third semester.
 * 
 * Constraints:
 * 1 <= n <= 15
 * 1 <= k <= n
 * 0 <= dependencies.length <= n * (n-1) / 2
 * dependencies[i].length == 2
 * 1 <= xi, yi <= n
 * xi != yi
 * All prerequisite relationships are distinct, that is, dependencies[i] != dependencies[j].
 * The given graph is a directed acyclic graph.
 * 
 */
#include <vector>
#include <algorithm>
#include <bitset>
#include <climits>
#include <functional>
using namespace std;

class Solution1 {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        // dp[i] : 学完状态 i 的课程所需的最少学期数 (i 的二进制位为1表示已学)
        vector<int> dp(1 << n, n);  // 初始化为最大值 n (最坏情况一学期一门)
        
        // pre[j] : 课程 j 的先修课程集合 (二进制位为1表示必须先修)
        vector<int> pre(n, 0);
        for (auto& r : relations) {
            int x = r[0] - 1, y = r[1] - 1;  // 转换为 0-based
            pre[y] |= (1 << x);
        }
        
        dp[0] = 0;  // 基础状态：什么都没学
        
        // 枚举所有已学课程的状态
        for (int state = 0; state < (1 << n); ++state) {
            // 找出当前学期可以学习的课程集合 canTake
            int canTake = 0;
            for (int j = 0; j < n; ++j) {
                // 如果课程 j 未学，且其所有先修课都已学 (pre[j] 是 state 的子集)
                if (!(state >> j & 1) && ((pre[j] & state) == pre[j])) {
                    canTake |= (1 << j);
                }
            }
            
            // 排除已经学过的课程 (实际上 canTake 已经排除了，但为了清晰保留)
            canTake &= ~state;
            
            // 枚举 canTake 的所有子集 sub，表示这一学期实际学习的课程
            // 技巧： (sub - 1) & canTake 可以枚举所有子集
            for (int sub = canTake; sub; sub = (sub - 1) & canTake) {
                if (__builtin_popcount(sub) <= k) {  // 一学期最多学 k 门
                    dp[state | sub] = min(dp[state | sub], dp[state] + 1);
                }
            }
            
            // 特殊情况：canTake 本身 <= k，可以直接学完
            if (__builtin_popcount(canTake) <= k) {
                dp[state | canTake] = min(dp[state | canTake], dp[state] + 1);
            }
        }
        
        return dp[(1 << n) - 1];  // 所有课程学完的状态
    }
};

class Solution2 {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> pre(n, 0);
        for (auto& r : relations) {
            int x = r[0] - 1, y = r[1] - 1;
            pre[y] |= (1 << x);
        }
        
        int full = (1 << n) - 1;
        vector<int> memo(1 << n, -1);
        
        function<int(int)> dfs = [&](int state) -> int {
            if (state == full) return 0;  // 所有课学完
            if (memo[state] != -1) return memo[state];
            
            // 找出当前可以学习的课程
            int canTake = 0;
            for (int j = 0; j < n; ++j) {
                if (!(state >> j & 1) && ((pre[j] & state) == pre[j])) {
                    canTake |= (1 << j);
                }
            }
            
            int res = INT_MAX;
            // 枚举子集
            if (__builtin_popcount(canTake) <= k) {
                // 可以一次性学完所有可学课程
                res = min(res, dfs(state | canTake) + 1);
            } else {
                for (int sub = canTake; sub; sub = (sub - 1) & canTake) {
                    if (__builtin_popcount(sub) == k) {  // 只枚举恰好学 k 门的子集
                        res = min(res, dfs(state | sub) + 1);
                    }
                }
                // 还需要考虑学少于 k 门的情况（例如可学课程数 > k，但最优解可能先学部分）
                // 但上面的循环已经包含小于 k 的情况（因为子集大小可以小于 k）
            }
            return memo[state] = res;
        };
        
        return dfs(0);
    }
};