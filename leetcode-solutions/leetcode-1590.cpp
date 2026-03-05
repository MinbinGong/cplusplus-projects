/**
 * 1590. Make Sum Divisible by P
 * 
 * Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
 * 
 * Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
 * 
 * A subarray is defined as a contiguous block of elements in the array.
 * 
 * Example 1:
 * Input: nums = [3,1,4,2], p = 6
 * Output: 1
 * Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
 * 
 * Example 2:
 * Input: nums = [6,3,5,2], p = 9
 * Output: 2
 * Explanation: The sum of the elements in nums is 16, which is not divisible by 9. We can remove the subarray [6,3], and the sum of the remaining elements is 10, which is divisible by 9.
 * 
 * Example 3:
 * Input: nums = [1,2,3], p = 3
 * Output: 0
 * Explanation: The sum of the elements in nums is 6, which is already divisible by 3. Thus, we do not need to remove anything.
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 1 <= p <= 10^9
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long sum = 0;
        for (int num : nums) sum += num;
        int target = sum % p;
        if (target == 0) return 0;          // 整个数组和已可被整除

        unordered_map<int, int> last;        // 记录每个前缀和模 p 的最后出现位置
        last[0] = -1;                         // 前缀和 0 在索引 -1 处
        int cur = 0;
        int n = nums.size();
        int ans = n;                           // 初始化为最大可能长度

        for (int i = 0; i < n; ++i) {
            cur = (cur + nums[i]) % p;
            int need = (cur - target + p) % p; // 需要的左前缀和模值
            if (last.count(need)) {
                ans = min(ans, i - last[need]);
            }
            last[cur] = i;                      // 更新当前前缀和的位置
        }

        return ans == n ? -1 : ans;
    }
};
