/**
 * 1558. Minimum Numbers of Function Calls to Make Target Array
 * 
 * Given an array nums of non-negative integers, you need to apply the following operations on the array:
 * 
 * If the number is even, divide it by 2.
 * If the number is odd, add 1 to it.
 * 
 * Return the minimum number of operations needed to make all the elements of the array equal to 0.
 * 
 * Example 1:
 * Input: nums = [1,5]
 * Output: 5
 * Explanation: 
 * All elements can be made equal to 0 in the following operations:
 * 1. Subtract 1 from 5. Now nums = [0,4].
 * 2. Divide 4 by 2. Now nums = [0,2].
 * 3. Divide 2 by 2. Now nums = [0,1].
 * 4. Subtract 1 from 1. Now nums = [0,0].
 * 
 * Example 2:
 * Input: nums = [2,2]
 * Output: 3
 * Explanation: 
 * All elements can be made equal to 0 in the following operations:
 * 1. Divide 2 by 2. Now nums = [0,2].
 * 2. Subtract 1 from 2. Now nums = [0,1].
 * 3. Subtract 1 from 1. Now nums = [0,0].
 * 
 * Example 3:
 * Input: nums = [4,2,5]
 * Output: 6
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;      // 总操作次数
        int mx = 0;        // 记录数组中的最大值

        for (int v : nums) {
            mx = max(mx, v);
            // 累加每个数字的二进制中 '1' 的个数，即所需的加1操作次数
            ans += __builtin_popcount(v);
        }

        // 如果最大值大于0，计算所需的全局乘2操作次数。
        // 31 - __builtin_clz(mx) 等价于 floor(log2(mx))，即最高位的位置。
        // 这代表了从1开始，通过不断乘2得到 mx 所需的次数。
        if (mx > 0) {
            ans += 31 - __builtin_clz(mx);
        }
        return ans;
    }
};