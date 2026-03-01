/*
 * 1301. Number of Paths with Max Score
 * 
 * You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
 * 
 * You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
 * 
 * Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
 * 
 * In case there is no path, return [0, 0].
 * 
 * Example 1:
 * Input: board = ["E23","2X2","12S"]
 * Output: [7,1]
 * 
 * Example 2:
 * Input: board = ["E12","1X1","21S"]
 * Output: [4,2]
 * 
 * Example 3:
 * Input: board = ["E11","XXX","11S"]
 * Output: [0,0]
 * 
 * Note:
 * 2 <= board.length == board[i].length <= 100
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        // dp[i][j].first 为最大得分，.second 为方案数
        vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>>(n + 1, {-1, 0}));
        
        // 将起点 S 视为数字 0
        board[n - 1][n - 1] = '0';
        // 将终点 E 视为数字 0（其实不加也行，因为最终结果不包含它）
        board[0][0] = '0';
        
        // 起点初始化：从 S 出发，得分为 0，方案数为 1
        dp[n - 1][n - 1] = {0, 1};
        
        // 从右下角往左上角遍历
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // 跳过起点（已初始化）和障碍物
                if ((i == n - 1 && j == n - 1) || board[i][j] == 'X') continue;
                
                // 从三个方向转移过来的最大得分
                int maxScore = max({
                    dp[i + 1][j].first,
                    dp[i][j + 1].first,
                    dp[i + 1][j + 1].first
                });
                
                if (maxScore < 0) continue; // 三个方向都不可达
                
                // 当前格子的数字（终点 E 视为 0）
                int cur = (board[i][j] == 'E') ? 0 : board[i][j] - '0';
                dp[i][j].first = maxScore + cur;
                
                // 方案数累加：只累加那些能达到 maxScore 的方向
                if (dp[i + 1][j].first == maxScore) {
                    dp[i][j].second = (dp[i][j].second + dp[i + 1][j].second) % MOD;
                }
                if (dp[i][j + 1].first == maxScore) {
                    dp[i][j].second = (dp[i][j].second + dp[i][j + 1].second) % MOD;
                }
                if (dp[i + 1][j + 1].first == maxScore) {
                    dp[i][j].second = (dp[i][j].second + dp[i + 1][j + 1].second) % MOD;
                }
            }
        }
        
        // 终点不可达
        if (dp[0][0].second == 0) return {0, 0};
        return {dp[0][0].first, dp[0][0].second};
    }
};