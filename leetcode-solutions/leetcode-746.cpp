/*
 * Min Cost Climbing Stairs
 *
 * You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
 * 
 * You can either start from the step with index 0, or the step with index 1.
 * 
 * Return the minimum cost to reach the top of the floor.
 * 
 * Example 1:
 * 
 * Input: cost = [10,15,20]
 * Output: 15
 * Explanation: Cheapest is: start on cost[1], pay that cost, and go to the top.
 * 
 * Example 2:
 * 
 * Input: cost = [1,100,1,1,1,100,1,1,100,1]
 * Output: 6
 * 
 * Note:
 * 1. cost will have a length in the range [2, 1000].
 * 2. Every cost[i] will be an integer in the range [0, 999].
 * 3. You can either start from the step with index 0, or the step with index 1.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        // dp[i] = minimum cost to reach step i
        // We can start at step 0 or 1, so dp[0] = cost[0], dp[1] = cost[1]
        // For i >= 2, dp[i] = cost[i] + min(dp[i-1], dp[i-2])
        // The answer is min(dp[n-1], dp[n-2]) because top is beyond last step
        int prev2 = cost[0];
        int prev1 = cost[1];
        for (int i = 2; i < n; ++i) {
            int curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return min(prev1, prev2);
    }
};