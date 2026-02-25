/*
 * 1012. Numbers With Repeated Digits
 *
 * Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.
 * 
 * Example 1:
 *
 * Input: 20
 * Output: 1
 * Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
 * 
 * Example 2:
 *
 * Input: 100
 * Output: 10
 * Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
 * 
 * Example 3:
 *
 * Input: 1000
 * Output: 262
 * 
 * Note:
 *
 * 1 <= N <= 10^9
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int numDupDigitsAtMostN(int N) {
        if (N < 10) return 0;                      // no repeated digits for 1..9
        
        string s = to_string(N);
        int len = s.size();
        
        // factorials for permutation calculation (0! to 10!)
        int fact[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
        
        // permutation P(n, k) = n! / (n-k)!
        auto P = [&](int n, int k) -> int {
            if (n < k) return 0;
            return fact[n] / fact[n - k];
        };
        
        // count numbers with fewer digits than N
        int unique = 0;
        for (int L = 1; L < len; ++L) {
            // first digit: 1..9 (9 choices), remaining L-1 digits: choose from remaining 9 digits (0..9 except the first)
            unique += 9 * P(9, L - 1);
        }
        
        // count numbers with exactly len digits, ≤ N
        vector<bool> used(10, false);
        for (int i = 0; i < len; ++i) {
            int digit = s[i] - '0';
            int start = (i == 0) ? 1 : 0;            // first digit cannot be zero
            
            // try all smaller digits at this position
            for (int d = start; d < digit; ++d) {
                if (!used[d]) {
                    // after placing d, we have used i+1 digits (previous i digits + d)
                    int usedCount = i + 1;
                    int remaining = len - i - 1;
                    int available = 10 - usedCount;
                    unique += P(available, remaining);
                }
            }
            
            // if current digit is already used, stop further counting
            if (used[digit]) {
                return N - unique;
            }
            used[digit] = true;
        }
        
        // N itself has all distinct digits
        unique += 1;
        return N - unique;
    }
};