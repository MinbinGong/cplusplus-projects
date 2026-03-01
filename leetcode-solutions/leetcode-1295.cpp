/**
 * 1295. Find Numbers with Even Number of Digits
 * 
 * Given an array nums of integers, return how many of them contain an even number of digits.
 * 
 * Example 1:
 * Input: nums = [12,345,2,6,7896]
 * Output: 2
 * Explanation: 
 * 12 contains 2 digits (even number of digits). 
 * 345 contains 3 digits (odd number of digits). 
 * 2 contains 1 digit (odd number of digits). 
 * 6 contains 1 digit (odd number of digits). 
 * 7896 contains 4 digits (even number of digits). 
 * Therefore only 12 and 7896 contain an even number of digits.
 * 
 * Example 2:
 * Input: nums = [555,901,482,1771]
 * Output: 1 
 * Explanation: 
 * Only 1771 contains an even number of digits.
 * 
 * Note:
 * 1 <= nums.length <= 500
 * 1 <= nums[i] <= 10^5
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution1 {
public:
    int findNumbers(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            if (to_string(num).length() % 2 == 0) {
                ans++;
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    int findNumbers(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            int digits = 0;
            int x = num;
            while (x) {
                x /= 10;
                digits++;
            }
            // 注意：如果 num == 0，digits 为 0，不算偶数，符合题意（0 通常视为1位）
            if (digits % 2 == 0) {
                ans++;
            }
        }
        return ans;
    }
};