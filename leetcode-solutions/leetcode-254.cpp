/*
 * Factor Combinations
 *
 * Numbers can be regarded as the product of their factors.
 *
 * For example, 8 = 2 x 2 x 2 = 2 x 4.
 * Given an integer n, return all possible combinations of its factors.
 * You may return the answer in any order.
 * 
 * Constraints:
 * 1. 1 <= n <= 107
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> result;
        vector<int> current;
        // 从因子2开始尝试，初始的目标是 n
        dfs(result, current, n, 2);
        return result;
    }

private:
    /**
     * 深度优先搜索函数
     * @param result  存储所有有效组合的结果集
     * @param current 当前正在构建的因子组合
     * @param target  当前需要分解的目标数
     * @param start   当前层可以尝试的起始因子，用于保证非递减序列
     */
    void dfs(vector<vector<int>>& result, vector<int>& current, int target, int start) {
        // 如果当前组合不为空，说明找到了一个有效的因子组合。
        // 注意：这里排除掉 [target] 自身的情况。
        if (!current.empty()) {
            // 将当前组合的副本与剩余的 target 组成一个完整组合加入结果集。
            // 例如：current = [2], target = 6，则此操作会加入组合 [2, 6]。
            current.push_back(target);
            result.push_back(current);
            current.pop_back(); // 回溯，恢复状态
        }

        // 从 start 开始尝试可能的因子 i，确保序列非递减
        // 循环条件 i * i <= target 是一个重要的剪枝优化：
        // 因为因子都是成对出现的，我们只需要找到较小的那个因子 i，
        // 较大的因子 j = target / i 会在下一层被处理或直接作为 target 的一部分。
        // 当 i 超过 sqrt(target) 时，另一部分 j 会小于 i，这可能会导致重复或递减序列。
        for (int i = start; i * i <= target; ++i) {
            // 如果 i 能整除 target，说明 i 是一个有效的因子
            if (target % i == 0) {
                current.push_back(i);                 // 选择因子 i
                dfs(result, current, target / i, i);  // 递归分解 target / i，且下一层从 i 开始
                current.pop_back();                    // 回溯，撤销选择
            }
        }
    }
};