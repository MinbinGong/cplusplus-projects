/*
 * 1708. Largest Subarray Length K
 * 
 * An array A is larger than some array B if for the first index i where A[i] != B[i], A[i] > B[i].
 * 
 * For example, consider 0-indexing:
 * [1,3,2,4] > [1,2,2,4], since at index 1, 3 > 2.
 * [1,4,4,4] < [2,1,1,1], since at index 0, 1 < 2.
 * A subarray is a contiguous sequence of elements within an array.
 * 
 * Given an integer array nums of distinct integers, return the largest subarray of nums of length k.
 * 
 * Example 1:
 * Input: nums = [1,4,5,2,3], k = 3
 * Output: [5,2,3]
 * Explanation: The subarrays of size 3 are: [1,4,5], [4,5,2], and [5,2,3].
 * Of these, [5,2,3] is the largest by lexicographical order.
 * 
 * Example 2:
 * Input: nums = [1,4,5,2,3], k = 4
 * Output: [4,5,2,3]
 * Explanation: The subarrays of size 4 are: [1,4,5,2] and [4,5,2,3].
 * Of these, [4,5,2,3] is the largest by lexicographical order.
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= k <= nums.length
 * nums[i] is distinct.
 * 
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    vector<int> largestSubarray(vector<int>& nums, int k) {
        // 只需要找到最佳起始位置
        int bestStart = 0;
        int n = nums.size();
        
        // 遍历所有可能的起始位置（0 到 n-k）
        for (int i = 1; i <= n - k; ++i) {
            if (nums[i] > nums[bestStart]) {
                bestStart = i;
            }
        }
        
        // 返回从 bestStart 开始长度为 k 的子数组
        return vector<int>(nums.begin() + bestStart, 
                          nums.begin() + bestStart + k);
    }
};

class Solution2 {
public:
    vector<int> largestSubarray(vector<int>& nums, int k) {
        auto it = max_element(nums.begin(), nums.begin() + nums.size() - k + 1);
        return {it, it + k};
    }
};