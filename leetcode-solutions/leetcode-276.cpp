/*
 * Paint Fence
 * 
 * There is a fence with n posts, each post can be painted with one of the k colors.
 * 
 * You have to paint all the posts such that no more than two adjacent fence posts have the same color.
 * 
 * Return the total number of ways you can paint the fence.
 * 
 * Example 1:
 * Input: n = 3, k = 2
 * Output: 6
 * Explanation: All the possibilities are shown.
 * Note that painting all the posts red or all the posts green is invalid because there must be at least two adjacent fence posts with the same color.
 * 
 * Example 2:
 * Input: n = 1, k = 1
 * Output: 1
 * 
 * Example 3:
 * Input: n = 7, k = 2
 * Output: 42
 * 
 * Constraints:
 * 1 <= n <= 50
 * 1 <= k <= 105
 * The testcases are generated such that the answer is in the range [0, 231 - 1] for the given n and k.
 */
class Solution {
public:
    int numWays(int n, int k) {
        if (n == 0) return 0;        // no posts
        if (n == 1) return k;         // only one post
        if (n == 2) return k * k;     // two posts, any combination

        // dp[i-2] and dp[i-1] for previous two steps
        long long prev2 = k;           // dp[1]
        long long prev1 = (long long)k * k; // dp[2]

        for (int i = 3; i <= n; ++i) {
            long long curr = (k - 1) * (prev1 + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return (int)prev1; // for n>=3, prev1 holds dp[n]
    }
};