/*
 * 1704. Determine if String Halves Are Alike
 * 
 * You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.
 * 
 * Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
 * 
 * Return true if a and b are alike. Otherwise, return false.
 * 
 * Example 1:
 * Input: s = "book"
 * Output: true
 * Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
 * 
 * Example 2:
 * Input: s = "textbook"
 * Output: false
 * Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
 * Notice that the vowel o is counted twice.
 * 
 * Constraints:
 * 2 <= s.length <= 1000
 * s.length is even.
 * s consists of uppercase and lowercase letters.
 * 
 */
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        // 1. 收集所有 1 的原始索引
        vector<long long> pos;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                pos.push_back(i);
            }
        }

        int m = pos.size(); // 1 的总数
        if (k > m) return 0; // 边界情况

        // 2. 构建前缀和数组，方便快速计算区间内索引之和
        // prefix[i] 表示 pos[0] 到 pos[i-1] 的和
        vector<long long> prefix(m + 1, 0);
        for (int i = 0; i < m; ++i) {
            prefix[i + 1] = prefix[i] + pos[i];
        }

        long long ans = LLONG_MAX;

        // 3. 滑动窗口，枚举所有可能的 k 个 1 的组合
        // 窗口在 pos 数组上滑动，索引范围 [i, i + k - 1]
        for (int i = 0; i + k - 1 < m; ++i) {
            int left = i;
            int right = i + k - 1;

            // 找到当前窗口的“中位数”位置。这是目标连续段的“锚点”。
            // 对于奇数个元素，中位数是中间那个；对于偶数个，选择左中位数或右中位数均可，这里选择左中位数。
            // 在 pos 数组中，这个中位数的索引是 mid_idx。
            int mid_idx = left + (k - 1) / 2;
            long long mid_pos = pos[mid_idx];

            // 计算将这些 1 移动到以 mid_pos 为中心的连续位置所需的总交换次数
            // 公式： (目标位置之和) - (当前位置之和)
            // 但需要分左右两侧分别计算，并减去因计算偏移产生的重复部分。

            // 计算左侧部分 (left 到 mid_idx - 1) 的代价
            // 左侧元素的目标位置应该是 [mid_pos - (mid_idx - left), mid_pos - 1]
            // 左侧元素当前的位置和可以通过前缀和快速获得
            int left_cnt = mid_idx - left;
            // 左侧目标位置之和：等差数列求和 (首项 + 末项) * 项数 / 2
            // 末项 = mid_pos - 1, 首项 = mid_pos - left_cnt
            long long left_target_sum = (mid_pos * 2 - left_cnt - 1) * left_cnt / 2;
            // 左侧当前位置之和
            long long left_current_sum = prefix[mid_idx] - prefix[left];
            long long left_cost = left_target_sum - left_current_sum;

            // 计算右侧部分 (mid_idx + 1 到 right) 的代价
            // 右侧元素的目标位置应该是 [mid_pos + 1, mid_pos + right_cnt]
            int right_cnt = right - mid_idx;
            // 右侧目标位置之和
            long long right_target_sum = (mid_pos * 2 + 1 + right_cnt) * right_cnt / 2;
            // 右侧当前位置之和
            long long right_current_sum = prefix[right + 1] - prefix[mid_idx + 1];
            long long right_cost = right_current_sum - right_target_sum;

            // 总代价是两侧代价之和
            long long total_cost = left_cost + right_cost;

            ans = min(ans, total_cost);
        }

        return ans;
    }
};