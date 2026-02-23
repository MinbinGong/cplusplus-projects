/*
 * 24 Game
 *
 * You have 4 cards each containing a number from 1 to 9. You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.
 * 
 * Example 1:
 *
 * Input: [4, 1, 8, 7]
 * Output: True
 * Explanation: (8-4) * (7-1) = 24
 * 
 * Example 2:
 *
 * Input: [1, 2, 1, 2]
 * Output: False
 * 
 * Note:
 *
 * The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
 * Every operation done is between two numbers. In particular, we cannot use - as a unary operator.
 * For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
 * You may assume that the given expression is always valid.
 * All intermediate results will be in the range of [-200, 200].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        // 将整数转换为双精度浮点数，便于处理除法
        vector<double> nums(cards.begin(), cards.end());
        return dfs(nums);
    }

private:
    // 递归回溯，尝试所有可能的运算组合
    bool dfs(vector<double>& nums) {
        int n = nums.size();
        // 如果只剩一个数字，检查是否等于24（考虑浮点误差）
        if (n == 1) return abs(nums[0] - 24) < 1e-6;

        // 选择两个不同的数字进行运算
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double a = nums[i], b = nums[j];

                // 所有可能的运算结果
                vector<double> candidates = {
                    a + b,
                    a - b,
                    b - a,
                    a * b
                };
                // 除法需要保证分母不为零
                if (abs(b) > 1e-6) candidates.push_back(a / b);
                if (abs(a) > 1e-6) candidates.push_back(b / a);

                // 构建剩余数字的列表（除了 i 和 j）
                vector<double> next;
                for (int k = 0; k < n; ++k) {
                    if (k != i && k != j) next.push_back(nums[k]);
                }

                // 尝试每个运算结果，加入剩余列表继续递归
                for (double val : candidates) {
                    next.push_back(val);
                    if (dfs(next)) return true;
                    next.pop_back();  // 回溯
                }
            }
        }
        return false;
    }
};