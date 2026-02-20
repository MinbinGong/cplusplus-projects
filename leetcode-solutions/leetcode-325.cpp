/*
 * Maximum Size Subarray Sum Equals k
 * 
 * Given an array nums and an integer k, return the maximum length of a subarray that sums to k.
 * If there is not one, return 0 instead.
 * 
 * Example 1:
 * Input: nums = [1,-1,5,-2,3], k = 3
 * Output: 4
 * Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
 * 
 * Example 2:
 * Input: nums = [-2,-1,2,1], k = 1
 * Output: 2
 * Explanation: The subarray [-1, 2] sums to 1 and is the longest.
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<long long, int> prefixSumIndex; // 记录前缀和第一次出现的位置
        long long sum = 0;
        int maxLen = 0;
        
        // 初始化：前缀和为0时，位置为-1（表示空数组）
        prefixSumIndex[0] = -1;
        
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            long long target = sum - k; // 需要找的前缀和
            
            // 如果存在前缀和为 target，则从该位置之后到 i 的和为 k
            if (prefixSumIndex.find(target) != prefixSumIndex.end()) {
                int len = i - prefixSumIndex[target];
                maxLen = max(maxLen, len);
            }
            
            // 只记录第一次出现的位置，以保证子数组最长
            if (prefixSumIndex.find(sum) == prefixSumIndex.end()) {
                prefixSumIndex[sum] = i;
            }
        }
        return maxLen;
    }
};