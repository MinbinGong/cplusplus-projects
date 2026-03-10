/**
 * 1726. Tuple with Same Product
 * 
 * Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
 * 
 * Example 1:
 * Input: nums = [2,3,4,6]
 * Output: 8
 * Explanation: There are 8 valid tuples:
 * (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
 * (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
 * 
 * Example 2:
 * Input: nums = [1,2,4,5,10]
 * Output: 16
 * Explanation: There are 16 valid tuples:
 * (1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
 * (2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
 * 
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 104
 * All elements in nums are distinct.
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> freq; // product -> number of pairs (i,j) with i<j

        // Count all pair products
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int prod = nums[i] * nums[j];
                ++freq[prod];
            }
        }

        long long ans = 0;
        for (auto& [_, cnt] : freq) {
            if (cnt >= 2) {
                // C(cnt,2) unordered pairs of pairs, each gives 8 ordered tuples
                // 8 * cnt*(cnt-1)/2 = 4 * cnt*(cnt-1)
                ans += 4LL * cnt * (cnt - 1);
            }
        }

        return (int)ans;
    }
};