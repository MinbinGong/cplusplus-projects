/*
 * 1599. Maximum Profit of Operating a Centennial Wheel
 *
 * You are the operator of a Centennial Wheel that has four gondolas, and each gondola has room for up to four people. You have the ability to rotate the gondolas counterclockwise, which costs you runningCost dollars.
 *
 * You are given an array customers of length n where customers[i] is the number of new customers arriving just before the ith rotation (0-indexed). This means you must rotate the wheel i times before the customers[i] customers arrive. You cannot make customers wait if there is room in the gondola. Each customer pays boardingCost dollars when they board on the gondola closest to the ground and will exit once that gondola reaches the ground again.
 *
 * You can stop the wheel at any time, including before serving all customers. If you decide to stop serving customers, all subsequent rotations are free in order to get all the customers down safely. Note that if there are currently more than four customers waiting at the wheel, only four will board the gondola, and the rest will wait for the next rotation.
 *
 * Example 1:
 * Input: customers = [8,3], boardingCost = 5, runningCost = 6
 * Output: 3
 * Explanation: The numbers written on the gondolas are the number of people currently there.
 * 1. 8 customers arrive, 4 board and 4 wait for the next gondola, the wheel rotates. Current profit is 4 * $5 - 6 = $14.
 * 2. 3 customers arrive, the 4 waiting board the wheel and the other 3 wait, the wheel rotates. Current profit is 8 * $5 - 6 = $28.
 * 3. The final 3 customers board the gondola, the wheel rotates. Current profit is 11 * $5 - 6 = $42.
 * So the maximum profit achievable is $42.
 * 
 * Example 2:
 * Input: customers = [10,9,6], boardingCost = 6, runningCost = 4
 * Output: 7
 * Explanation:
 * 1. 10 customers arrive, 4 board and 6 wait for the next gondola, the wheel rotates. Current profit is 4 * $6 - 4 = $20.
 * 2. 9 customers arrive, 4 board and 5 wait for the next gondola, the wheel rotates. Current profit is 8 * $6 - 4 = $40.
 * 3. The final 6 customers arrive, 4 board and 2 wait for the next gondola, the wheel rotates. Current profit is 12 * $6 - 4 = $60.
 * 4. 4 board and 2 wait for the next gondola, the wheel rotates. Current profit is 16 * $6 - 4 = $80.
 * 5. 2 board and 0 wait for the next gondola, the wheel rotates. Current profit is 18 * $6 - 4 = $92.
 * 
 * Constraints:
 * n == customers.length
 * 1 <= n <= 105
 * 0 <= customers[i] <= 50
 * 1 <= boardingCost, runningCost <= 100
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int n = customers.size();
        int waiting = 0;
        long long profit = 0;
        long long maxProfit = LLONG_MIN;   // 记录历史最大利润
        int result = -1;                    // 对应最大利润的最早轮次

        int i = 1;                           // 轮次从1开始计数
        while (i <= n || waiting > 0) {      // 还有游客未到达或等待队列非空
            if (i - 1 < n) {                  // 第i轮之前有新的游客到达
                waiting += customers[i - 1];
            }
            int take = min(4, waiting);       // 本轮最多上4人
            waiting -= take;
            profit += take * boardingCost - runningCost;

            if (profit > maxProfit) {          // 发现更大的利润
                maxProfit = profit;
                result = i;                    // 记录当前轮次
            }
            ++i;
        }

        return maxProfit >= 0 ? result : -1;   // 最大利润为负时返回-1
    }
};