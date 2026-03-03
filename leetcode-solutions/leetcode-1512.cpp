/**
 * 1512. Number of Good Pairs
 * 
 * Given an array of integers nums, return the number of good pairs.
 * A pair (i, j) is called good if nums[i] == nums[j] and i < j.
 * 
 * Example 1:
 * Input: nums = [1,2,3,1,1,3]
 * Output: 4
 * Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
 * 
 * Example 2:
 * Input: nums = [1,1,1,1]
 * Output: 6
 * Explanation: Each pair in the array are good.
 * 
 * Example 3:
 * Input: nums = [1,2,3]
 * Output: 0
 * 
 * Note:
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 * 
 */
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 方法1：哈希表优化解法 O(n)
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int, int> count;
        int result = 0;
        
        for (int num : nums) {
            // 当前数字可以和之前出现的所有相同数字形成好数对
            result += count[num];
            count[num]++;
        }
        
        return result;
    }
    
    // 方法2：暴力解法 O(n²)
    int numIdenticalPairsBruteForce(vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] == nums[j]) {
                    result++;
                }
            }
        }
        
        return result;
    }
};