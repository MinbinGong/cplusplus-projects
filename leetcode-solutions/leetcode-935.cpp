/*
 * Knight Dialer
 *
 * The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagaram:
 *
 * A chess knight can move as indicated in the chess diagram below:
 *
 * We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
 *
 * Given an integer n, return how many distinct phone numbers of length n we can dial.
 *
 * You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
 *
 * As the answer may be very large, return the answer modulo 109 + 7.
 *
 * Example 1:
 * Input: n = 1
 * Output: 10
 * Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
 * 
 * Example 2:
 * Input: n = 2
 * Output: 20
 * Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]
 * 
 * Note:
 * 1 <= n <= 5000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int knightDialer(int n) {
        const int MOD = 1e9 + 7;
        
        // 每个数字可以跳到的下一个数字
        vector<vector<int>> moves = {
            {4, 6},     // 0
            {6, 8},     // 1
            {7, 9},     // 2
            {4, 8},     // 3
            {0, 3, 9},  // 4
            {},         // 5（不能跳到任何数字）
            {0, 1, 7},  // 6
            {2, 6},     // 7
            {1, 3},     // 8
            {2, 4}      // 9
        };
        
        // dp[i] 表示当前步数下，以数字 i 结尾的不同号码数量
        vector<long long> dp(10, 1);  // 第 1 步（n=1），每个数字本身作为号码
        
        // 进行 n-1 次跳跃
        for (int step = 2; step <= n; ++step) {
            vector<long long> new_dp(10, 0);
            for (int num = 0; num < 10; ++num) {
                for (int next : moves[num]) {
                    new_dp[next] = (new_dp[next] + dp[num]) % MOD;
                }
            }
            dp = move(new_dp);
        }
        
        // 计算所有数字的总和
        long long ans = 0;
        for (long long count : dp) {
            ans = (ans + count) % MOD;
        }
        return ans;
    }
};