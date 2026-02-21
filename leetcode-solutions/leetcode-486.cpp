/*
 * Predict the Winner
 *
 *  You are given an integer array nums. Two players are playing a game with this array: player 1 and player 2.
 *
 *  Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a score of 0. At each turn, the player takes one of the numbers from either end of the array (i.e., nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1. The player adds the chosen number to their score. The game ends when there are no more elements in the array.
 *
 *  Return true if Player 1 can win the game. If the scores of both players are equal, then player 1 is still the winner, and you should also return true. You may assume that both players are playing optimally.
 *
 *  Constraints:
 *  1 <= nums.length <= 20
 *  0 <= nums[i] <= 107
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        // dp[i][j] 表示在子数组 nums[i..j] 中，当前玩家与对手的分数差的最大值
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // 初始化长度为1的子数组
        for (int i = 0; i < n; ++i) {
            dp[i][i] = nums[i];
        }
        
        // 按长度递增计算
        for (int len = 1; len < n; ++len) {
            for (int i = 0; i + len < n; ++i) {
                int j = i + len;
                // 当前玩家可以选择左端或右端，然后减去对手在剩余区间的最优分数差
                dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
            }
        }
        
        // 如果最终分数差非负，玩家1获胜
        return dp[0][n-1] >= 0;
    }
};