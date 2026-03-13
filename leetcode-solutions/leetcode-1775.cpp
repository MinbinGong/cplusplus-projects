/**
 * 1775. Equal Sum Arrays With Minimum Number of Operations
 * 
 * You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.
 * 
 * In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.
 * 
 * Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.
 * 
 * Example 1:
 * 
 * Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
 * Output: 3
 * Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
 * - Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
 * - Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
 * - Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
 * 
 * Example 2:
 * 
 * Input: nums1 = [1,1,1,1,1,1,1], nums2 = [6]
 * Output: -1
 * Explanation: There is no way to decrease the sum of nums1 or to increase the sum of nums2 to make them equal.
 * 
 * Example 3:
 * 
 * Input: nums1 = [6,6], nums2 = [1]
 * Output: 3
 * Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
 * - Change nums1[0] to 2. nums1 = [2,6], nums2 = [1].
 * - Change nums1[1] to 2. nums1 = [2,2], nums2 = [1].
 * - Change nums2[0] to 4. nums1 = [2,2], nums2 = [4].
 * 
 * Constraints:
 * 
 * n == nums1.length
 * m == nums2.length
 * 1 <= m, n <= 105
 * 1 <= nums1[i], nums2[i] <= 6
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        
        // 保证 sum1 <= sum2，方便处理
        if (sum1 > sum2) {
            swap(nums1, nums2);
            swap(sum1, sum2);
        }
        
        int diff = sum2 - sum1;
        if (diff == 0) return 0;
        
        // 可行性判断
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 * 6 < n2 * 1 || n1 * 1 > n2 * 6) return -1;

        // cnt[i] 表示增益为 i 的元素个数，i 从 1 到 5
        vector<int> cnt(6, 0); 
        
        // 统计和较小数组的可增加量
        for (int num : nums1) {
            cnt[6 - num]++; // 变成6能增加的数值
        }
        // 统计和较大数组的可减少量
        for (int num : nums2) {
            cnt[num - 1]++; // 变成1能减少的数值
        }

        int ans = 0;
        // 从最大的增益 5 开始遍历
        for (int i = 5; i >= 1; --i) {
            if (diff <= 0) break;
            if (cnt[i] > 0) {
                // 每次操作能缩小 i 的差值
                // 需要的操作次数 = min(当前元素个数, ceil(剩余差值 / i))
                int need = min(cnt[i], (diff + i - 1) / i);
                ans += need;
                diff -= need * i;
            }
        }
        
        return diff <= 0 ? ans : -1;
    }
};

class Solution2 {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        
        if (sum1 == sum2) return 0;
        // 确保 sum1 是较小的和
        if (sum1 > sum2) {
            return minOperations(nums2, nums1);
        }

        // 可行性判断
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 * 6 < n2 * 1) return -1;

        int diff = sum2 - sum1;
        vector<int> gains;
        
        // 收集增益：nums1 增加
        for (int num : nums1) {
            gains.push_back(6 - num);
        }
        // 收集增益：nums2 减少
        for (int num : nums2) {
            gains.push_back(num - 1);
        }
        
        // 从大到小排序
        sort(gains.begin(), gains.end(), greater<int>());
        
        int ans = 0;
        for (int gain : gains) {
            if (diff <= 0) break;
            diff -= gain;
            ans++;
        }
        
        return diff <= 0 ? ans : -1;
    }
};