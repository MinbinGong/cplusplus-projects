/*
 * 1049. Last Stone Weight II
 *
 * We have a collection of rocks, each rock has a positive integer weight.
 * 
 * Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:
 * 
 * If x == y, both stones are totally destroyed;
 * If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
 * At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)
 * 
 * Example 1:
 * Input: [2,7,4,1,8,1]
 * Output: 1
 * Explanation: 
 * We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
 * we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
 * we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
 * we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.
 * 
 * Example 2:
 * Input: [31,26,33,21,40]
 * Output: 5
 * Explanation: 
 * We can combine 26 and 33 to get 7 so the array converts to [31,7,21,40] then,
 * we can combine 31 and 40 to get 7 so the array converts to [7,21,7] then,
 * we can combine 21 and 7 to get 14 so the array converts to [14,7] then,
 * we can combine 14 and 7 to get 7 so the array converts to [7] then that's the optimal value.
 * 
 * Note:
 * 1. 1 <= stones.length <= 30
 * 2. 1 <= stones[i] <= 100
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>
#include <bitset>
using namespace std;

class Solutio1 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        if (n == 0) return 0;
        
        // 计算总重量
        int total = accumulate(stones.begin(), stones.end(), 0);
        int target = total / 2; // 目标是找到最接近total/2的子集和
        
        // 动态规划：0-1背包问题
        // dp[j]表示能否凑出重量j
        vector<bool> dp(target + 1, false);
        dp[0] = true; // 重量0总是可以凑出
        
        // 遍历所有石头
        for (int stone : stones) {
            // 从后向前遍历，避免重复使用同一块石头
            for (int j = target; j >= stone; j--) {
                if (dp[j - stone]) {
                    dp[j] = true;
                }
            }
        }
        
        // 找到最接近target的可凑重量
        int maxWeight = 0;
        for (int j = target; j >= 0; j--) {
            if (dp[j]) {
                maxWeight = j;
                break;
            }
        }
        
        // 最后剩下的石头重量 = total - 2 * maxWeight
        return total - 2 * maxWeight;
    }
};

class Solution2 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int total = accumulate(stones.begin(), stones.end(), 0);
        int target = total / 2;
        
        // dp[j]表示能凑出的最大重量（不超过j）
        vector<int> dp(target + 1, 0);
        
        for (int stone : stones) {
            for (int j = target; j >= stone; j--) {
                dp[j] = max(dp[j], dp[j - stone] + stone);
            }
        }
        
        return total - 2 * dp[target];
    }
};

class Solution3 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int total = accumulate(stones.begin(), stones.end(), 0);
        int target = total / 2;
        
        // 使用bitset记录所有可能的和
        bitset<3001> dp; // 题目限制：最多30块石头，每块最多100，所以最大总重3000
        dp[0] = 1;
        
        for (int stone : stones) {
            dp |= dp << stone;
        }
        
        // 找到最接近target的可凑重量
        for (int j = target; j >= 0; j--) {
            if (dp[j]) {
                return total - 2 * j;
            }
        }
        
        return total;
    }
};