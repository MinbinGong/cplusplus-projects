/**
 * 1140. Stone Game II
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Alex and Lee continue their games with piles of stones.  There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].  The objective of the game is to end with the most stones. 
 * 
 * Alex and Lee take turns, with Alex starting first.  Initially, M = 1.
 * 
 * On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).
 * 
 * The game continues until all the stones have been taken.
 * 
 * Assuming Alex and Lee play optimally, return the maximum number of stones Alex can get.
 * 
 * Example 1:
 * Input: piles = [2,7,9,4,4]
 * Output: 10
 * Explanation: 
 * Alex can take all the stones in the first 4 piles to win the game.
 * 
 * Example 2:
 * Input: piles = [1,2,3,4,5,100]
 * Output: 104
 * 
 * Note:
 * 1 <= piles.length <= 100
 * 1 <= piles[i] <= 10^4
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        // 后缀和，suffix[i] 表示从 i 到 n-1 的石子总数
        vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = suffix[i + 1] + piles[i];
        }
        // 记忆化数组，memo[i][M] 表示从第 i 堆开始，当前 M 值时先手能获得的最大石子数
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        
        function<int(int, int)> dfs = [&](int i, int M) {
            if (i == n) return 0;
            if (memo[i][M] != -1) return memo[i][M];
            int best = 0;
            // 当前玩家可以取 X 堆，1 <= X <= 2 * M
            for (int X = 1; X <= 2 * M && i + X <= n; ++X) {
                int cur = suffix[i] - suffix[i + X];           // 本轮拿走的石子
                int nextM = max(M, X);                         // 下一轮的 M
                // 剩余石子为 suffix[i+X]，对手从 i+X 开始的最优收益是 dfs(i+X, nextM)
                // 那么当前玩家最终收益 = cur + (剩余 - 对手收益)
                int total = cur + (suffix[i + X] - dfs(i + X, nextM));
                best = max(best, total);
            }
            memo[i][M] = best;
            return best;
        };
        
        return dfs(0, 1);
    }
};