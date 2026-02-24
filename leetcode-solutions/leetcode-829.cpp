/**
 * 829. Consecutive Numbers Sum
 *
 * Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?
 *
 * Example:
 * Input: 5
 * Output: 2
 * Explanation: 5 = 5 = 2 + 3
 *
 * Input: 9
 * Output: 3
 * Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4
 *
 * Input: 15
 * Output: 4
 * Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
 *
 * Note: 1 <= N <= 10 ^ 9.
 *
 */
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int count = 0;
        // k is the length of the consecutive sequence
        for (int k = 1; k * (k + 1) / 2 <= N; ++k) {
            int numerator = N - k * (k - 1) / 2;
            if (numerator % k == 0) {
                ++count;   // found a valid starting number a = numerator / k
            }
        }
        return count;
    }
};