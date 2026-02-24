/**
 * 837. New 21 Game
 * 
 * Alice plays the following game, loosely based on the card game "21".
 * 
 * Alice starts with 0 points, and draws numbers while she has less than K points.  During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.  Each draw is independent and the outcomes have equal probabilities.
 * 
 * Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?
 * 
 * Example:
 * Input: N = 10, K = 1, W = 10
 * Output: 1.00000
 * Explanation:  Alice gets a single card, then stops.
 * 
 * Input: N = 6, K = 1, W = 10
 * Output: 0.60000
 * Explanation:  Alice gets a single card, then stops.
 * In 6 out of W = 10 possibilities, she is at or below N = 6 points.
 * 
 * Note:
 * 1 <= K <= N <= 10000
 * 1 <= W <= 10000
 * Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 * The judging time limit has been reduced for this question.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    double new21Game(int N, int K, int W) {
        // If K == 0, the game ends immediately with score 0, which is ≤ N.
        if (K == 0) return 1.0;

        // dp[i] = probability of reaching total score i.
        // We only need indices up to K+W-1 because scores cannot exceed that.
        vector<double> dp(K + W, 0.0);
        dp[0] = 1.0;

        double window = 0.0; // sliding sum of the last W dp values that are < K
        for (int i = 1; i < K + W; ++i) {
            // Add dp[i-1] to the window if it is a state from which we can draw.
            if (i - 1 < K) window += dp[i - 1];
            // Remove dp[i-W-1] if it falls out of the window and was a valid drawing state.
            if (i - W - 1 >= 0 && i - W - 1 < K) window -= dp[i - W - 1];
            dp[i] = window / W;
        }

        double ans = 0.0;
        // Sum probabilities of final scores between K and min(N, K+W-1).
        for (int i = K; i <= N && i < K + W; ++i) {
            ans += dp[i];
        }
        return ans;
    }
};