/*
 * 1648. Sell Diminishing-Valued Colored Balls
 *
 * You have an inventory of different colored balls, and there is a customer that wants orders balls of any color.
 * The customer weirdly values the colored balls. Each colored ball's value is the number of balls of that color you currently have in your inventory. For example, if you own 6 yellow balls, the customer would pay 6 for the first yellow ball. After the transaction, there are only 5 yellow balls left, so the next yellow ball is then valued at 5 (i.e., the value of the balls decreases as you sell more to the customer).
 * You are given an integer array, inventory, where inventory[i] represents the number of balls of the ith color that you initially own. You are also given an integer orders, which represents the total number of balls that the customer wants. You can sell the balls in any order.
 * Return the maximum total value that you can attain after selling orders colored balls. As the answer may be too large, return it modulo 109 + 7.
 * 
 * Example 1:
 * Input: inventory = [2,5], orders = 4
 * Output: 14
 * Explanation: Sell the 1st color 1 time (value 2) and the 2nd color 3 times (value 5 + 4 + 3).
 * The maximum total value is 2 + 5 + 4 + 3 = 14.
 * 
 * Example 2:
 * Input: inventory = [3,5], orders = 6
 * Output: 19
 * Explanation: Sell the 1st color 2 times (value 3 + 2) and the 2nd color 4 times (value 5 + 4).
 * The maximum total value is 3 + 2 + 5 + 4 = 19.
 * 
 * Constraints:
 * 1 <= inventory.length <= 10^5
 * 1 <= inventory[i] <= 10^9
 * 1 <= orders <= min(sum(inventory[i]), 10^9)
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        const int MOD = 1e9 + 7;
        long long left = 0, right = *max_element(inventory.begin(), inventory.end());
        long long threshold = 0; // 二分查找的阈值

        // 1. 二分查找阈值，使得价值高于该阈值的球总数 >= orders
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long total = 0; // 记录价值高于 mid 的球的总数
            for (int num : inventory) {
                if (num > mid) {
                    total += num - mid;
                }
            }
            // 如果总数 >= orders，说明阈值可能还可以更高
            if (total >= orders) {
                threshold = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // 2. 计算价值总和
        long long ans = 0;
        long long extra = 0; // 记录超出阈值的球的总数
        for (int num : inventory) {
            if (num > threshold) {
                extra += num - threshold;
                // 使用等差数列求和公式计算从 threshold+1 到 num 的和
                // 公式: (首项 + 末项) * 项数 / 2
                ans = (ans + (num + threshold + 1) * (num - threshold) / 2) % MOD;
            }
        }

        // 3. 处理多余的球
        // extra 是价值高于 threshold 的球总数，可能超过 orders
        // 需要减去多卖的部分，多卖的部分每个球价值为 (threshold+1)
        long long overSold = extra - orders;
        ans = (ans - (threshold + 1) * overSold % MOD + MOD) % MOD;

        return ans;
    }
};