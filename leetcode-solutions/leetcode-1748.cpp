/**
 * 1748. Sum of Unique Elements
 * 
 * You are given an integer array nums. The unique elements of an array are the
 * elements that appear exactly once in the array.
 * 
 * Return the sum of all the unique elements of nums.
 * 
 * Example 1:
 * 
 * Input: nums = [1,2,3,2]
 * Output: 4
 * Explanation: The unique elements are [1,3], and the sum is 4.
 * 
 * Example 2:
 * 
 * Input: nums = [1,1,1,1,1]
 * Output: 0
 * Explanation: There are no unique elements, and the sum is 0.
 * 
 * Example 3:
 * 
 * Input: nums = [1,2,3,4,5]
 * Output: 15
 * Explanation: The unique elements are [1,2,3,4,5], and the sum is 15.
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 * 
 */
#include <unordered_map>
#include <vector>
using namespace std;

class Solution1 {
public:
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, int> freq;
        // 统计每个数字的出现次数
        for (int num : nums) {
            freq[num]++;
        }
        
        int sum = 0;
        // 累加出现次数为1的数字
        for (auto& [num, cnt] : freq) {
            if (cnt == 1) {
                sum += num;
            }
        }
        return sum;
    }
};

class Solution2 {
public:
    int sumOfUnique(vector<int>& nums) {
        int count[101] = {0}; // 假设数值范围 1~100
        for (int num : nums) {
            count[num]++;
        }
        int sum = 0;
        for (int i = 1; i <= 100; i++) {
            if (count[i] == 1) {
                sum += i;
            }
        }
        return sum;
    }
};