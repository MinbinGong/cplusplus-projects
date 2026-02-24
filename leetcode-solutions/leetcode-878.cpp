/**
 * 878. Nth Magical Number
 *
 * A positive integer is magical if it is divisible by either a or b.
 * Given the three integers n, a, and b, return the nth magical number.
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * Example 1:
 * Input: n = 1, a = 2, b = 3
 * Output: 2
 *
 * Example 2:
 * Input: n = 4, a = 2, b = 3
 * Output: 6
 *
 * Note:
 * 1 <= n <= 10^9
 * 2 <= a, b <= 4 * 10^4
 *
 */
#include <iostream>
using namespace std;

class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
        const int MOD = 1e9 + 7;
        long long lcm = (long long)A / gcd(A, B) * B; // 最小公倍数
        long long left = min(A, B), right = (long long)N * min(A, B); // 右边界足够大
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long cnt = mid / A + mid / B - mid / lcm; // 容斥原理
            if (cnt < N) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left % MOD;
    }

private:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};