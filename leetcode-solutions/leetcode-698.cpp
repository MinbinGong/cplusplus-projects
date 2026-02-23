/*
 * Partition to K Equal Sum Subsets
 * 
 * Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.
 * 
 * Example 1:
 * 
 * Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 * Output: True
 * Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 * 
 * Note:
 * 1. 1 <= k <= len(nums) <= 16.
 * 2. 0 < nums[i] < 10000.
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) return false;
        int target = sum / k;
        sort(nums.begin(), nums.end(), greater<int>()); // 降序排序，优先放大的数，减少回溯
        if (nums[0] > target) return false; // 最大值超过目标，不可能
        
        vector<bool> visited(nums.size(), false);
        return backtrack(nums, visited, 0, k, 0, target);
    }

private:
    bool backtrack(vector<int>& nums, vector<bool>& visited, int curSum, int k, int start, int target) {
        if (k == 1) return true; // 只剩一个子集，剩下的数一定能组成目标
        if (curSum == target) {
            // 完成一个子集，开始下一个，从0重新开始选择
            return backtrack(nums, visited, 0, k - 1, 0, target);
        }
        for (int i = start; i < nums.size(); ++i) {
            if (!visited[i] && curSum + nums[i] <= target) {
                visited[i] = true;
                if (backtrack(nums, visited, curSum + nums[i], k, i + 1, target))
                    return true;
                visited[i] = false;
                // 剪枝：如果当前和为0，说明这个数放在开头都无法成功，直接跳出
                if (curSum == 0) break;
                // 跳过相同值，避免重复尝试
                while (i + 1 < nums.size() && nums[i + 1] == nums[i]) ++i;
            }
        }
        return false;
    }
};
