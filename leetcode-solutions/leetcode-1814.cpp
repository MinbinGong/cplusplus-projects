/*
 * 1814. Count Nice Pairs in an Array
 * 
 * You are given an array nums that consists of non-negative integers. Let us define rev(x) as the reverse of the non-negative integer x. For example, rev(123) = 321, and rev(120) = 21. A pair of indices (i, j) is nice if it satisfies all of the following conditions:
 * 
 * 0 <= i < j < nums.length
 * nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
 * Return the number of nice pairs of indices. Since that number can be too large, return it modulo 109 + 7.
 * 
 * Example 1:
 * 
 * Input: nums = [42,11,1,97]
 * Output: 2
 * Explanation: The two pairs are:
 * (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
 * (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.
 * 
 * Example 2:
 * 
 * Input: nums = [13,10,35,24,76]
 * Output: 4
 * Explanation: The four pairs are:
 * (0,1) : 13 + rev(10) = 13 + 10 = 23, 10 + rev(13) = 10 + 31 = 41.
 * (0,4) : 42 + rev(76) = 42 + 67 = 109, 76 + rev(42) = 76 + 24 = 100.
 * (1,3) : 11 + rev(24) = 11 + 42 = 53, 24 + rev(11) = 24 + 11 = 35.
 * (2,3) : 35 + rev(24) = 35 + 42 = 77, 24 + rev(35) = 24 + 53 = 77.
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 105
 * 0 <= nums[i] <= 109
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int countNicePairs(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        unordered_map<int, int> freq;
        long long ans = 0;
        for (int num : nums) {
            int diff = num - rev(num);
            ans = (ans + freq[diff]) % MOD;
            freq[diff]++;
        }
        return ans;
    }

private:
    int rev(int n) {
        int r = 0;
        while (n > 0) {
            r = r * 10 + n % 10;
            n /= 10;
        }
        return r;
    }
};