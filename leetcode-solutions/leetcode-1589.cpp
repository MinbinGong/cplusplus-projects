/**
 * 1589. Maximum Sum Obtained of Any Permutation
 * 
 * We have an array of integers, nums, and an array of requests where requests[i] = [starti, endi]. The ith request asks for the sum of nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi]. Both starti and endi are 0-indexed.
 * 
 * Return the maximum total sum of all requests among all permutations of nums.
 * 
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
 * Output: 19
 * Explanation: One permutation of nums is [2,1,3,4,5] with the following result: 
 * requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
 * requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
 * Total sum: 8 + 3 = 19
 * 
 * 
 * Example 2:
 * Input: nums = [1,2,3,4,5,6], requests = [[0,1]]
 * Output: 11
 * Explanation: One permutation of nums is [6,5,4,3,2,1] with the following result: 
 * requests[0] -> nums[0] + nums[1] = 6 + 5 = 11
 * Total sum: 11
 * 
 * Example 3:
 * Input: nums = [1,2,3,4,5,10], requests = [[0,2],[1,3],[1,1]]
 * Output: 47
 * Explanation: One permutation of nums is [4,10,5,3,2,1] with the following result: 
 * requests[0] -> nums[0] + nums[1] + nums[2] = 4 + 10 + 5 = 19
 * requests[1] -> nums[1] + nums[2] + nums[3] = 10 + 5 + 3 = 18
 * requests[2] -> nums[1] = 10
 * Total sum: 19 + 18 + 10 = 47
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 1 <= requests.length <= 10^5
 * requests[i].length == 2
 * 0 <= starti <= endi < nums.length
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<int> diff(n + 1, 0); // 差分数组
        for (auto& req : requests) {
            int l = req[0], r = req[1];
            diff[l]++;
            diff[r + 1]--;
        }
        
        // 计算每个位置的覆盖次数
        vector<int> cnt(n);
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += diff[i];
            cnt[i] = cur;
        }
        
        // 排序：覆盖次数多的位置与较大的数相乘
        sort(cnt.begin(), cnt.end());
        sort(nums.begin(), nums.end());
        
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = (ans + (long long)cnt[i] * nums[i]) % MOD;
        }
        return ans;
    }
};
