/**
 * 1467. Probability of a Two Boxes Having The Same Number of Distinct Balls
 * 
 * Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i.
 * 
 * All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).
 * 
 * Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] (a) (Please read the explanation of the first example carefully).
 * 
 * We want to calculate the probability that the two boxes have the same number of distinct balls.
 * 
 * Example 1:
 * 
 * Input: balls = [1,1]
 * Output: 1.00000
 * Explanation: Only 2 ways to divide the balls equally:
 * - [1] (1)
 * - [1] (1)
 * 
 * Example 2:
 * 
 * Input: balls = [2,1,1]
 * Output: 0.66667
 * Explanation: We have the set of balls [1, 1, 2, 3]
 * This set of balls will be shuffled randomly and we may have one of the 12 distinct shuffles with equal probability (i.e. 1/12):
 * [1,1 / 2,3], [1,1 / 3,2], [1,2 / 1,3], [1,2 / 3,1], [1,3 / 1,2], [1,3 / 2,1], [2,1 / 1,3], [2,1 / 3,1], [2,3 / 1,1], [3,1 / 1,2], [3,1 / 2,1], [3,2 / 1,1]
 * After that, we add the first two balls to the first box and the remaining two balls to the other box.
 * 
 * Note:
 * 1 <= balls.length <= 8
 * 1 <= balls[i] <= 6
 * sum(balls) is even.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double getProbability(vector<int>& balls) {
        int total = accumulate(balls.begin(), balls.end(), 0);
        if (total % 2 != 0) return 0.0;               // cannot split equally
        int half = total / 2;
        int n = balls.size();
        vector<int> cur(n);                            // current assignment for each colour
        long long totalWays = 0, favorable = 0;

        // depth‑first search over colours
        function<void(int, int)> dfs = [&](int idx, int sumA) {
            if (idx == n) {
                if (sumA == half) {
                    int distA = 0, distB = 0;
                    for (int i = 0; i < n; ++i) {
                        if (cur[i] > 0) distA++;
                        if (cur[i] < balls[i]) distB++;
                    }
                    // number of ways for this particular count vector
                    long long prod = 1;
                    for (int i = 0; i < n; ++i) {
                        prod *= comb(balls[i], cur[i]);
                    }
                    totalWays += prod;
                    if (distA == distB) favorable += prod;
                }
                return;
            }
            int maxTake = min(balls[idx], half - sumA);
            for (int take = 0; take <= maxTake; ++take) {
                cur[idx] = take;
                dfs(idx + 1, sumA + take);
            }
        };

        dfs(0, 0);
        return static_cast<double>(favorable) / totalWays;
    }

private:
    // binomial coefficient C(n, k) for small numbers
    long long comb(int n, int k) {
        if (k < 0 || k > n) return 0;
        if (k > n - k) k = n - k;
        long long res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * (n - k + i) / i;
        }
        return res;
    }
};
