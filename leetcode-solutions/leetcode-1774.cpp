/**
 * 1774. Closest Dessert Cost
 * 
 * You would like to make dessert and are preparing to buy the ingredients. You have n ice cream base flavors and m types of toppings to choose from. You must follow these rules when making your dessert:
 * 
 * There must be exactly one ice cream base.
 * You can add one or more types of topping or have no toppings at all.
 * There are at most two of each type of topping.
 * You are given three inputs:
 * 
 * baseCosts, an integer array of length n, where each baseCosts[i] represents the price of the ith ice cream base flavor.
 * toppingCosts, an integer array of length m, where each toppingCosts[i] is the price of one of the ith topping.
 * target, an integer representing your target price for dessert.
 * You want to make a dessert with a total cost as close to target as possible.
 * 
 * Return the closest possible cost of the dessert to target. If there are multiple, return the lower one.
 * 
 * Example 1:
 * 
 * Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
 * Output: 10
 * Explanation: Consider the following combination (all 0-indexed):
 * - Choose base 1: cost 7
 * - Take 1 of topping 0: cost 1 x 3 = 3
 * - Take 0 of topping 1: cost 0 x 4 = 0
 * Total: 7 + 3 + 0 = 10.
 * 
 * Example 2:
 * 
 * Input: baseCosts = [2,3], toppingCosts = [4,5,100], target = 18
 * Output: 17
 * Explanation: Consider the following combination (all 0-indexed):
 * - Choose base 1: cost 3
 * - Take 1 of topping 0: cost 1 x 4 = 4
 * - Take 2 of topping 1: cost 2 x 5 = 10
 * - Take 0 of topping 2: cost 0 x 100 = 0
 * Total: 3 + 4 + 10 + 0 = 17. You cannot make a dessert with a total cost of 18.
 * 
 * Example 3:
 * 
 * Input: baseCosts = [3,10], toppingCosts = [2,5], target = 9
 * Output: 8
 * Explanation: It is possible to make desserts with cost 8 and 10. Return 8 as it is the lower cost.
 * 
 * Constraints:
 * 
 * n == baseCosts.length
 * m == toppingCosts.length
 * 1 <= n, m <= 10
 * 1 <= baseCosts[i], toppingCosts[i] <= 104
 * 1 <= target <= 104
 * 
 */
#include <vector>
#include <climits>
using namespace std;

class Solution1 {
private:
    int bestCost = INT_MAX; // 记录最优成本

    void dfs(vector<int>& toppingCosts, int target, int index, int currentSum) {
        // 如果当前总和已经远远超过最优解的可能性，可以剪枝优化（可选）
        // if (abs(currentSum - target) > abs(bestCost - target) && currentSum > target) return;

        if (index == toppingCosts.size()) {
            // 到达末尾，比较并更新最优解
            int currentDiff = abs(currentSum - target);
            int bestDiff = abs(bestCost - target);
            if (bestCost == INT_MAX || currentDiff < bestDiff || (currentDiff == bestDiff && currentSum < bestCost)) {
                bestCost = currentSum;
            }
            return;
        }

        // 三种选择：不加，加一份，加两份
        dfs(toppingCosts, target, index + 1, currentSum);
        dfs(toppingCosts, target, index + 1, currentSum + toppingCosts[index]);
        dfs(toppingCosts, target, index + 1, currentSum + toppingCosts[index] * 2);
    }

public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        bestCost = INT_MAX;
        for (int base : baseCosts) {
            // 以每个基料为起点开始 DFS
            dfs(toppingCosts, target, 0, base);
        }
        return bestCost;
    }
};

class Solution2 {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        // 价格上限可以设为 target 加上最大可能的配料成本，但为了简单，设一个较大值
        const int MAX_COST = 20000; 
        vector<bool> dp(MAX_COST + 1, false);

        // 1. 初始化基料
        for (int base : baseCosts) {
            dp[base] = true;
        }

        // 2. 处理配料，每种配料做两次01背包
        for (int topping : toppingCosts) {
            // 做两次，代表最多选两份
            for (int time = 0; time < 2; ++time) {
                // 从大到小遍历，避免重复使用当前配料
                for (int cost = MAX_COST; cost >= topping; --cost) {
                    if (dp[cost - topping]) {
                        dp[cost] = true;
                    }
                }
            }
        }

        // 3. 寻找最接近 target 的成本
        int ans = -1;
        // 从 target 向两边扩散查找
        for (int diff = 0; diff <= MAX_COST; ++diff) {
            // 检查 target - diff
            if (target - diff >= 0 && dp[target - diff]) {
                ans = target - diff;
                break;
            }
            // 检查 target + diff
            if (target + diff <= MAX_COST && dp[target + diff]) {
                ans = target + diff;
                break;
            }
        }
        return ans;
    }
};