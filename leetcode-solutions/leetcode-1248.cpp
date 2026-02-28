/*
 * 1248. Count Number of Nice Subarrays
 *
 * Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
 *
 * Return the number of nice sub-arrays.
 *
 * Example 1:
 * Input: nums = [1,1,2,1,1], k = 3
 * Output: 2
 * Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
 *
 * Example 2:
 * Input: nums = [2,4,6], k = 1
 * Output: 0
 * Explanation: There is no odd numbers in the array.
 *
 * Example 3:
 * Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
 * Output: 16
 *
 * Constraints:
 * 1 <= nums.length <= 50000
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= nums.length
 * 
 */
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> prefixCount;
        prefixCount[0] = 1;  // 初始状态，奇数个数为0出现了1次
        int oddCount = 0;
        int result = 0;
        
        for (int num : nums) {
            // 如果当前数字是奇数，则奇数计数加1
            if (num % 2 == 1) {
                oddCount++;
            }
            
            // 如果存在前缀使得 (oddCount - k) 出现，则加上这个前缀的数量
            if (prefixCount.find(oddCount - k) != prefixCount.end()) {
                result += prefixCount[oddCount - k];
            }
            
            // 更新当前奇数个数的前缀计数
            prefixCount[oddCount]++;
        }
        
        return result;
    }
};