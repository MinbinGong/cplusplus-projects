/*
 * 1808. Maximize Number of Nice Divisors
 *
 * You are given a positive integer primeFactors. You are asked to construct a positive integer n that satisfies the following conditions:
 * 
 * The number of prime factors of n (not necessarily distinct) is at most primeFactors.
 * The number of nice divisors of n is maximized. Note that a divisor of n is nice if it is divisible by every prime factor of n. For example, if n = 12, then its prime factors are [2,2,3], then 6 and 12 are nice divisors, while 3 and 4 are not.
 * Return the number of nice divisors of n. Since that number can be too large, return it modulo 109 + 7.
 * 
 * Example 1:
 * 
 * Input: primeFactors = 5
 * Output: 6
 * Explanation: 200 is a valid value of n.
 * 
 * Example 2:
 * 
 * Input: primeFactors = 8
 * Output: 18
 * Explanation: 280 is a valid value of n, and it has more nice divisors than 200.
 * 
 * Constraints:
 * 
 * 1 <= primeFactors <= 109
 * 
 */
class Solution {
private:
    const int MOD = 1e9 + 7;

    // 快速幂函数，计算 (a^n) % MOD
    long long fastPower(long long a, long long n) {
        long long ans = 1;
        while (n > 0) {
            if (n & 1) { // 如果当前二进制位为1
                ans = (ans * a) % MOD;
            }
            a = (a * a) % MOD; // a 自乘
            n >>= 1; // n 右移一位
        }
        return ans;
    }

public:
    int maxNiceDivisors(int primeFactors) {
        // 处理小规模情况
        if (primeFactors < 4) {
            return primeFactors;
        }

        // 根据余数分情况计算
        if (primeFactors % 3 == 0) {
            return fastPower(3, primeFactors / 3);
        } else if (primeFactors % 3 == 1) {
            // 余数为1时，拆出一个4，其余为3
            return (fastPower(3, primeFactors / 3 - 1) * 4) % MOD;
        } else { // primeFactors % 3 == 2
            // 余数为2时，拆出一个2，其余为3
            return (fastPower(3, primeFactors / 3) * 2) % MOD;
        }
    }
};