/*
 * Shopping Offers
 *
 * In LeetCode Store, there are some kinds of items to sell. Each item has a price.
 * 
 * However, there are some special offers, and a special offer consists of one or more different kinds of items with
 * a sale price.
 * 
 * You are given the each item's price, a set of special offers, and the number we need to buy for each item. The job
 * is to output the lowest price you have to pay for exactly certain items as given, where you could make optimal use
 * of the special offers.
 * 
 * Each special offer is represented in the form of an array, the last number represents the price you need to pay for
 * this special offer, other numbers represents how many specific items you could get if you buy this offer.
 * 
 * You could use any of special offers as many times as you want.
 * 
 * Example 1:
 * Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
 * Output: 14
 * Explanation: 
 * There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
 * The special offers are [3A,0B,5] and [1A,2B,10]. 
 * You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
 * 
 * Example 2:
 * Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
 * Output: 11
 * Explanation: 
 * The price of A is $2, and $3 for B, $4 for C. 
 * You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C. 
 * You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 for 1C. 
 * You cannot add more items, though only $9 for 2A ,2B and 1C.
 * 
 * Note:
 * There are at most 6 kinds of items, 100 special offers.
 * For each item, you need to buy at most 6 of them.
 * You are not allowed to buy more items than you want, even if that would lower the overall price.
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        // 备忘录，存储已计算过的需求状态对应的最小花费
        map<vector<int>, int> memo;
        return dfs(price, special, needs, memo);
    }

private:
    int dfs(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, map<vector<int>, int>& memo) {
        // 如果已经计算过，直接返回
        if (memo.count(needs)) return memo[needs];

        // 先计算不使用任何优惠的花费（直接原价购买）
        int minCost = 0;
        for (int i = 0; i < needs.size(); ++i) {
            minCost += needs[i] * price[i];
        }

        // 尝试每一个优惠套餐
        for (auto& offer : special) {
            vector<int> newNeeds = needs;
            bool valid = true;
            // 检查优惠是否可用，并更新新需求
            for (int i = 0; i < needs.size(); ++i) {
                if (offer[i] > newNeeds[i]) {
                    valid = false;
                    break;
                }
                newNeeds[i] -= offer[i];
            }
            if (valid) {
                // 递归计算使用该优惠后的最小花费
                int cost = offer.back() + dfs(price, special, newNeeds, memo);
                minCost = min(minCost, cost);
            }
        }

        // 记录结果到备忘录
        memo[needs] = minCost;
        return minCost;
    }
};