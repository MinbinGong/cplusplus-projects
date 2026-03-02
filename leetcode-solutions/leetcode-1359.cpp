/*
 * 1359. Count All Valid Pickup and Delivery Options
 *
 * Given n orders, each order consist in pickup and delivery services. 
 * 
 * Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i). 
 * 
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: n = 1
 * Output: 1
 * Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
 * 
 * Example 2:
 * Input: n = 2
 * Output: 6
 * Explanation: All possible orders: 
 * (P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and (P2,D2,P1,D1).
 * We can such that the delivery of second order is always after of the pickup of second order.
 * 
 * Example 3:
 * Input: n = 3
 * Output: 90
 * 
 * Note:
 * 1 <= n <= 500
 * 
 */
class Solution {
public:
    int countOrders(int n) {
        const int MOD = 1e9 + 7;
        long long ans = 1;
        for (int i = 1; i <= n; ++i) {
            ans = ans * i % MOD;               // multiply by i
            ans = ans * (2 * i - 1) % MOD;     // multiply by (2i-1)
        }
        return ans;
    }
};