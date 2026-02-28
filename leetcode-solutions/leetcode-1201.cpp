/*
 * 1201. Ugly Number III
 *
 * Write a program to find the n-th ugly number.
 * 
 * Ugly numbers are positive integers which are divisible by a or b or c.
 * 
 * Example 1:
 * Input: n = 3, a = 2, b = 3, c = 5
 * Output: 4
 * Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
 * 
 * Example 2:
 * Input: n = 4, a = 2, b = 3, c = 4
 * Output: 6
 * Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 12... The 4th is 6.
 * 
 * Example 3:
 * Input: n = 5, a = 2, b = 11, c = 13
 * Output: 10
 * Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13... The 5th is 10.
 * 
 * Example 4:
 * Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
 * Output: 1999999984
 * Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
 * 
 * Note:
 * 1 <= n, a, b, c <= 10^9
 * 1 <= a * b * c <= 10^18
 * It's guaranteed that the result will be in range [1, 2 * 10^9]
 * 
 */
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        long long lo = 1, hi = 2000000000000000000LL; // 2e18
        long long A = a, B = b, C = c;

        // safe lcm with cap to avoid overflow
        auto lcm = [&](long long x, long long y) -> long long {
            long long g = __gcd(x, y);
            if (x / g > hi / y) return hi + 1; // will be > any possible mid
            return x / g * y;
        };

        long long ab = lcm(A, B);
        long long ac = lcm(A, C);
        long long bc = lcm(B, C);
        long long abc = lcm(ab, C); // lcm of all three

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            long long cnt = mid / A + mid / B + mid / C
                          - mid / ab - mid / ac - mid / bc
                          + mid / abc;
            if (cnt < n) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};