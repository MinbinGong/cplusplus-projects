/*
 * 1824. Minimum Sideway Jumps
 * 
 * There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n. A frog starts at point 0 in the second lane and wants to jump to point n. However, there could be obstacles along the way.
 * 
 * You are given an array obstacles of length n + 1 where each obstacles[i] (ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i. If obstacles[i] == 0, there are no obstacles at point i. There will be at most one obstacle in the 3 lanes at each point.
 * 
 * For example, if obstacles[2] == 1, then there is an obstacle on lane 1 at point 2.
 * The frog can only travel from point i to point i + 1 on the same lane if there is not an obstacle on the lane at point i + 1. To avoid obstacles, the frog can also perform a side jump to jump to another lane (even if they are not adjacent) at the same point if there is no obstacle on the new lane.
 * 
 * Example 1:
 * Input: obstacles = [0,1,2,3,0]
 * Output: 2 
 * Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps (red arrows).
 * Note that the frog can jump over obstacles only when making side jumps (as shown at point 2).
 * 
 * Example 2:
 * Input: obstacles = [0,1,1,3,3,0]
 * Output: 0
 * Explanation: There are no obstacles on lane 2. No side jumps are required.
 * 
 * Example 3:
 * Input: obstacles = [0,2,1,0,3,0]
 * Output: 2
 * Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps.
 * 
 * Constraints:
 * 
 * obstacles.length == n + 1
 * 1 <= n <= 5 * 10^5
 * 0 <= obstacles[i] <= 3
 * obstacles[0] == obstacles[n] == 0
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int minSideJumps(vector<int>& obstacles) {
        // dp[j] 代表到达当前位置的第 j+1 条跑道所需的最少侧跳次数
        // 初始化：青蛙在点 0，位于跑道 2（索引1），因此到达跑道2需要0次，跑道1和3需要1次
        vector<int> dp = {1, 0, 1};
        const int INF = 1e9;

        // 从点 1 遍历到点 n (obstacles.size() - 1)
        for (int i = 1; i < obstacles.size(); ++i) {
            int obstacle = obstacles[i]; // 当前点有障碍的跑道 (1, 2, 3 或 0)

            // 1. 将有障碍的跑道标记为不可达 (设为无穷大)
            for (int lane = 0; lane < 3; ++lane) {
                if (obstacle == lane + 1) {
                    dp[lane] = INF;
                }
            }

            // 2. 找出当前所有可达跑道中的最小侧跳次数
            int minJumps = min({dp[0], dp[1], dp[2]});

            // 3. 尝试从最小跳数的跑道侧跳到当前跑道 (如果当前跑道没有障碍)
            for (int lane = 0; lane < 3; ++lane) {
                if (obstacle != lane + 1) {
                    // 比较：保持原样 dp[lane] 和 从其他地方跳过来 minJumps + 1
                    dp[lane] = min(dp[lane], minJumps + 1);
                }
            }
        }

        // 最终答案是到达最后一点时，三条跑道的最小值
        return *min_element(dp.begin(), dp.end());
    }
};

class Solution2 {
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size();
        // dp[i][j] 表示到达点 i 的第 j+1 条跑道的最小侧跳次数
        vector<vector<int>> dp(n, vector<int>(3, 1e9));
        
        // 初始化点 0
        dp[0][1] = 0;      // 跑道2
        dp[0][0] = 1;      // 跑道1
        dp[0][2] = 1;      // 跑道3

        for (int i = 1; i < n; ++i) {
            // 第一步：先考虑直行的情况 (从上一个位置的同一跑道过来)
            for (int lane = 0; lane < 3; ++lane) {
                if (obstacles[i] != lane + 1) { // 当前跑道没有障碍
                    dp[i][lane] = dp[i-1][lane];
                }
            }
            
            // 第二步：考虑侧跳的情况 (在当前点从其他跑道跳过来)
            for (int lane = 0; lane < 3; ++lane) {
                if (obstacles[i] == lane + 1) continue; // 当前跑道有障碍，跳过
                
                // 从另外两条跑道侧跳到当前跑道
                int other1 = (lane + 1) % 3;
                int other2 = (lane + 2) % 3;
                dp[i][lane] = min(dp[i][lane], min(dp[i][other1], dp[i][other2]) + 1);
            }
        }

        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};