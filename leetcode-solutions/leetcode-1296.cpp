/**
 * 1296. Divide Array in Sets of K Consecutive Numbers
 * 
 * Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into sets of k consecutive numbers
 * Return True if its possible otherwise return False.
 * 
 * Example 1:
 * Input: nums = [1,2,3,3,4,4,5,6], k = 4
 * Output: true
 * Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
 * 
 * Example 2:
 * Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
 * Output: true
 * Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
 * 
 * Example 3:
 * Input: nums = [3,3,2,2,1,1], k = 3
 * Output: true
 * 
 * Example 4:
 * Input: nums = [1,2,3,4], k = 3
 * Output: false
 * Explanation: Each array should be divided in subarrays of size 3.
 * 
 * Note:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= nums.length
 * 
 */
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int n = nums.size();
        // 长度必须能被k整除
        if (n % k != 0) return false;
        if (k == 1) return true; // 每个数字单独一组，总是可行

        // 统计每个数字的出现次数
        map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        // 按数字从小到大遍历
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            if (it->second == 0) continue; // 已被用完，跳过
            int num = it->first;
            int cnt = it->second; // 当前数字剩余次数，必须作为cnt个序列的开头
            // 检查后续连续k-1个数字是否都有至少cnt次
            for (int i = 0; i < k; ++i) {
                int cur = num + i;
                if (freq[cur] < cnt) return false;
                freq[cur] -= cnt; // 消耗掉cnt次
            }
        }
        return true;
    }
};
