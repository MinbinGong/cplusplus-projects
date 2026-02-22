/*
 * Number of Longest Increasing Subsequence
 *
 * Given an unsorted array of integers, find the number of longest increasing subsequence.
 *
 * Example 1:
 *
 * Input: [1,3,5,4,7]
 * Output: 2
 * Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
 *
 * Example 2:
 *
 * Input: [2,2,2,2,2]
 * Output: 5
 * Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1,
 * so output 5.
 *
 * Note:
 *
 * The number of nodes in the given tree will be at most 10000.
 * Each node's value is an integer in the range [0, 10^9].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> length(n, 1);  // LIS length ending at i
        vector<int> count(n, 1);   // number of LIS ending at i
        
        int maxLen = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    if (length[j] + 1 > length[i]) {
                        length[i] = length[j] + 1;
                        count[i] = count[j];
                    } else if (length[j] + 1 == length[i]) {
                        count[i] += count[j];
                    }
                }
            }
            maxLen = max(maxLen, length[i]);
        }
        
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (length[i] == maxLen) {
                result += count[i];
            }
        }
        return result;
    }
};