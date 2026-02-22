/*
 * Split Array with Equal Sum
 *
 * Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:
 * 0 < i, i + 1 < j, j + 1 < k < n - 1
 * Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
 * where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
 * 
 * Note:
 * 1 <= n <= 2000.
 * Elements in the given array will be in range [-1,000,000, 1,000,000].
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        // 至少需要 7 个元素才能分成 4 个非空子数组
        if (n < 7) return false;

        // 1. 构建前缀和数组
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // 2. 枚举中间分隔点 j
        for (int j = 3; j <= n - 4; ++j) {
            unordered_set<int> seen; // 存储可行的左半部分和

            // 3. 枚举左边的 i
            for (int i = 1; i <= j - 2; ++i) {
                int sum1 = prefix[i];                     // [0, i-1]
                int sum2 = prefix[j] - prefix[i + 1];     // [i+1, j-1]
                if (sum1 == sum2) {
                    seen.insert(sum1); // 记录前两个子数组相等的和
                }
            }

            // 4. 枚举右边的 k
            for (int k = j + 2; k <= n - 2; ++k) {
                int sum3 = prefix[k] - prefix[j + 1];     // [j+1, k-1]
                int sum4 = prefix[n] - prefix[k + 1];     // [k+1, n-1]
                if (sum3 == sum4 && seen.count(sum3)) {
                    return true; // 找到了合法的 i, j, k
                }
            }
        }
        return false;
    }
};