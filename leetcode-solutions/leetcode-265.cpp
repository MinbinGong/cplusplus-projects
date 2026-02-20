/*
 * Paint House II
 * 
 * There are a row of n houses, each house can be painted with one of the k colors. 
 * The cost of painting each house with a certain color is different. 
 * You have to paint all the houses such that no two adjacent houses have the same color.
 * 
 * The cost of painting each house with a certain color is represented by an n x k cost matrix costs.
 * 
 * For example, costs[0][0] is the cost of painting house 0 with color 0; 
 * costs[1][2] is the cost of painting house 1 with color 2, and so on...
 * 
 * Return the minimum cost to paint all houses.
 * 
 * Constraints:
 * 1. costs.length == n
 * 2. costs[i].length == k
 * 3. 1 <= n <= 100
 * 4. 2 <= k <= 20
 * 5. 1 <= costs[i][j] <= 20
 * 
 */
#include <vector>
using namespace std;

// 时间复杂度：O(nk^2)
// 空间复杂度：O(nk)
class Solution1 {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        int k = costs[0].size();
        
        // dp[i][j] 表示前 i+1 个房子，第 i 个房子颜色为 j 的最小花费
        vector<vector<int>> dp(n, vector<int>(k, INT_MAX));
        dp[0] = costs[0];
        
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                // 寻找前一个房子的最小花费（颜色不能为 j）
                int minPrev = INT_MAX;
                for (int c = 0; c < k; ++c) {
                    if (c == j) continue;
                    minPrev = min(minPrev, dp[i-1][c]);
                }
                dp[i][j] = costs[i][j] + minPrev;
            }
        }
        
        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};

// 时间复杂度：O(nk)
// 空间复杂度：O(k)
class Solution2 {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) return 0;
        int n = costs.size();
        int k = costs[0].size();
        
        // 记录前一个房子的最小值和次小值，以及最小值对应的颜色
        int prevMin1 = 0, prevMin2 = 0;
        int prevMinColor = -1;
        
        for (int i = 0; i < n; ++i) {
            int currMin1 = INT_MAX, currMin2 = INT_MAX;
            int currMinColor = -1;
            
            for (int j = 0; j < k; ++j) {
                // 根据当前颜色是否与上一个最小值颜色冲突，选择最小值或次小值
                int cost = costs[i][j] + (j == prevMinColor ? prevMin2 : prevMin1);
                
                // 更新当前房子的最小值和次小值
                if (cost < currMin1) {
                    currMin2 = currMin1;
                    currMin1 = cost;
                    currMinColor = j;
                } else if (cost < currMin2) {
                    currMin2 = cost;
                }
            }
            
            prevMin1 = currMin1;
            prevMin2 = currMin2;
            prevMinColor = currMinColor;
        }
        
        return prevMin1;
    }
};