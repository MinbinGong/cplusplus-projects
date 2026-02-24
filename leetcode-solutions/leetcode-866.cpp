/**
 * 866. Prime Palindrome
 * 
 * Example 1:
 * Input: 6
 * Output: 7
 * 
 * Example 2:
 * Input: 8
 * Output: 11
 * 
 * Example 3:
 * Input: 13
 * Output: 101
 * 
 * Note:
 * 1 <= N <= 10^8
 * The answer is guaranteed to exist and be less than 2 * 10^8.
 * 
 */
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:
    int primePalindrome(int N) {
        // Precompute primes up to 20000 (sqrt(2e8) ≈ 14142, safe margin)
        static vector<int> primes = []() {
            const int MAX = 20000;
            vector<bool> is_prime(MAX + 1, true);
            is_prime[0] = is_prime[1] = false;
            for (int i = 2; i * i <= MAX; ++i) {
                if (is_prime[i]) {
                    for (int j = i * i; j <= MAX; j += i)
                        is_prime[j] = false;
                }
            }
            vector<int> res;
            for (int i = 2; i <= MAX; ++i)
                if (is_prime[i]) res.push_back(i);
            return res;
        }();

        // primality test using trial division with precomputed primes
        auto isPrime = [&](long long n) -> bool {
            if (n < 2) return false;
            if (n == 2) return true;
            if (n % 2 == 0) return false;
            int limit = sqrt(n);
            for (int p : primes) {
                if (p > limit) break;
                if (n % p == 0) return false;
            }
            return true;
        };

        // check if a number is palindrome
        auto isPalindrome = [](int n) -> bool {
            int rev = 0, orig = n;
            while (n) {
                rev = rev * 10 + n % 10;
                n /= 10;
            }
            return rev == orig;
        };

        // construct an odd-length palindrome from its first half
        auto makePalindrome = [](int half, int len) -> long long {
            long long p = half;
            long long temp = half / 10;   // remove middle digit
            while (temp > 0) {
                p = p * 10 + temp % 10;
                temp /= 10;
            }
            return p;
        };

        // handle small numbers (including the only even-length prime palindrome 11)
        if (N <= 11) {
            for (int i = N; i <= 11; ++i) {
                if (isPrime(i) && isPalindrome(i))
                    return i;
            }
        }

        // generate odd-length palindromes (1,3,5,7,9 digits)
        for (int len = 1; len <= 9; len += 2) {
            int half_len = (len + 1) / 2;          // number of digits in the first half
            int start = 1;
            for (int i = 1; i < half_len; ++i) start *= 10;   // 10^(half_len-1)
            int end = start * 10 - 1;
            for (int half = start; half <= end; ++half) {
                long long p = makePalindrome(half, len);
                if (p >= N && isPrime(p))
                    return p;
            }
        }
        return -1;   // should never happen for given constraints
    }
};