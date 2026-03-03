/**
 * 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
 * 
 * Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
 * 
 * Example 1:
 * 
 * Input: nums = [8,2,4,7], limit = 4
 * Output: 2 
 * Explanation: All subarrays are: 
 * [8] with maximum absolute diff |8-8| = 0 <= 4.
 * [8,2] with maximum absolute diff |8-2| = 6 > 4. 
 * [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
 * [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
 * [2] with maximum absolute diff |2-2| = 0 <= 4.
 * 
 * Example 2:
 * 
 * Input: nums = [10,1,2,4,7,2], limit = 5
 * Output: 4 
 * Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
 * 
 * Example 3:
 * 
 * Input: nums = [4,2,2,2,4,4,2,2], limit = 0
 * Output: 3
 * 
 * Note:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 0 <= limit <= 10^9
 * 
 */
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> maxDeque; // stores indices of elements in decreasing order (max at front)
        deque<int> minDeque; // stores indices of elements in increasing order (min at front)
        int left = 0;
        int result = 0;

        for (int right = 0; right < nums.size(); ++right) {
            // maintain maxDeque: pop back while current value is larger
            while (!maxDeque.empty() && nums[maxDeque.back()] < nums[right]) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(right);

            // maintain minDeque: pop back while current value is smaller
            while (!minDeque.empty() && nums[minDeque.back()] > nums[right]) {
                minDeque.pop_back();
            }
            minDeque.push_back(right);

            // shrink window from left until max - min <= limit
            while (nums[maxDeque.front()] - nums[minDeque.front()] > limit) {
                if (maxDeque.front() == left) maxDeque.pop_front();
                if (minDeque.front() == left) minDeque.pop_front();
                ++left;
            }

            result = max(result, right - left + 1);
        }

        return result;
    }
};