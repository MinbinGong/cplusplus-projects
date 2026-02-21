/*
 * Largest Palindrome Product
 *
 * Find the largest palindrome made from the product of two n-digit numbers.
 * 
 * Constraints:
 * 1 <= n <= 8
 * 
 */
#include <cmath>
using namespace std;

class Solution {
public:
    int largestPalindrome(int n) {
        // Special case: for n=1, the largest palindrome product is 9 (3*3)
        if (n == 1) return 9;

        long long upper = pow(10, n) - 1;   // largest n-digit number
        long long lower = pow(10, n - 1);   // smallest n-digit number

        // Generate palindromes of length 2n in descending order
        for (long long left = upper; left >= lower; --left) {
            // Build the palindrome: left + reverse(left)
            long long p = left;
            long long tmp = left;
            while (tmp) {
                p = p * 10 + (tmp % 10);
                tmp /= 10;
            }
            // Now p is a palindrome with 2n digits
            // Check if it can be factored into two n-digit numbers
            for (long long i = upper; i * i >= p; --i) {
                if (p % i == 0) {
                    long long j = p / i;
                    if (j >= lower && j <= upper) {
                        return p % 1337;
                    }
                }
            }
        }
        return 0; // should never reach here
    }
};