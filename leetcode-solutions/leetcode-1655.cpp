/*
 * 1655. Distribute Repeating Integers
 *
 * You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:
 * 
 * The ith customer gets exactly quantity[i] integers,
 * The integers the ith customer gets are all equal, and
 * Every customer is satisfied.
 * Return true if it is possible to distribute nums according to the above conditions.
 * 
 * Example 1:
 * Input: nums = [1,2,3,4], quantity = [2]
 * Output: false
 * Explanation: The 0th customer cannot be given two different integers.
 * 
 * Example 2:
 * Input: nums = [1,2,3,3], quantity = [2]
 * Output: true
 * Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.
 * 
 * Example 3:
 * Input: nums = [1,1,2,2], quantity = [2,2]
 * Output: true
 * Explanation: The 0th customer is given [1,1], and the 1st customer is given [2,2].
 * 
 * Constraints:
 * n == nums.length
 * 1 <= n <= 105
 * 1 <= nums[i] <= 1000
 * m == quantity.length
 * 1 <= m <= 10
 * 1 <= quantity[i] <= 105
 * There are at most 50 unique values in nums.
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        // 1. 统计每个数字的出现次数
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // 将频数转为数组，并按降序排序（优化：优先使用大的频数）
        vector<int> counts;
        for (auto& p : freq) {
            counts.push_back(p.second);
        }
        sort(counts.rbegin(), counts.rend());
        
        int m = quantity.size();
        int n = counts.size();
        
        // 2. 预处理每个子集的需求总量
        vector<int> subsetSum(1 << m, 0);
        for (int mask = 0; mask < (1 << m); mask++) {
            for (int j = 0; j < m; j++) {
                if (mask >> j & 1) {
                    subsetSum[mask] = subsetSum[mask ^ (1 << j)] + quantity[j];
                    break;
                }
            }
        }
        
        // 3. DP 状态定义：dp[i][mask] 表示前 i 个频数能否满足子集 mask 的顾客
        // 由于 n 最多 50，2^m 最多 1024，空间可以接受
        vector<vector<bool>> dp(n + 1, vector<bool>(1 << m, false));
        dp[0][0] = true;
        
        // 4. 状态转移
        for (int i = 0; i < n; i++) {
            for (int mask = 0; mask < (1 << m); mask++) {
                if (!dp[i][mask]) continue; // 当前状态不可达，跳过
                
                // 不选用当前频数，直接转移到下一行
                dp[i + 1][mask] = true;
                
                // 尝试将当前频数分配给 mask 的某个补集子集
                int remain = ((1 << m) - 1) ^ mask; // 未满足的顾客
                for (int sub = remain; sub > 0; sub = (sub - 1) & remain) {
                    // 如果当前频数足够满足子集 sub 的需求
                    if (counts[i] >= subsetSum[sub]) {
                        dp[i + 1][mask | sub] = true;
                    }
                }
            }
        }
        
        return dp[n][(1 << m) - 1];
    }
};

class Solution2 {
private:
    bool ans = false;
    
    void backtrack(vector<int>& counts, vector<int>& quantity, int idx) {
        if (ans) return;                     // 已找到解，提前返回
        if (idx == quantity.size()) {         // 所有顾客都已分配
            ans = true;
            return;
        }
        
        // 尝试为第 idx 个顾客分配一个数字
        for (int i = 0; i < counts.size(); i++) {
            if (counts[i] >= quantity[idx]) {
                counts[i] -= quantity[idx];   // 分配
                backtrack(counts, quantity, idx + 1);
                counts[i] += quantity[idx];   // 回溯
            }
        }
    }
    
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        // 统计频数
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // 转为数组并按降序排序（优化：优先分配大频数）
        vector<int> counts;
        for (auto& p : freq) {
            counts.push_back(p.second);
        }
        sort(counts.rbegin(), counts.rend());
        
        // 将顾客需求量按降序排序（优化：优先处理需求大的顾客）
        sort(quantity.rbegin(), quantity.rend());
        
        // 剪枝：如果某个顾客的需求大于所有频数的最大值，直接返回 false
        if (quantity[0] > counts[0]) return false;
        
        ans = false;
        backtrack(counts, quantity, 0);
        return ans;
    }
};