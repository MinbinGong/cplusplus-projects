/**
 * 1621. Number of Sets of K Non-Overlapping Line Segments
 * 
 * Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, find the number of ways we can draw exactly k non-overlapping line segments such that each segment covers two or more points. The endpoints of each segment must have integral coordinates. The k line segments do not have to cover all n points, and they are allowed to share endpoints.
 * 
 * Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.
 * 
 * Example 1:
 * Input: n = 4, k = 2
 * Output: 5
 * Explanation: 
 * The two line segments are shown in red and blue.
 * The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
 * 
 * Example 2:
 * Input: n = 3, k = 1
 * Output: 3
 * Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.
 * 
 * Example 3:
 * Input: n = 30, k = 7
 * Output: 796297179
 * Explanation: The total number of possible ways to draw 7 line segments is 3796297200. Taking this number modulo 109 + 7 gives us 796297179.
 * 
 * Constraints:
 * 2 <= n <= 1000
 * 1 <= k <= n-1
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numberOfSets(int n, int k) {
        if (2 * k > n) return 0;               // impossible
        const int MOD = 1e9 + 7;
        
        // precompute factorials and inverse factorials up to n
        vector<long long> fact(n + 1), invFact(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i % MOD;
        
        // Fermat's little theorem: a^(MOD-2) ≡ a^(-1) (mod MOD)
        invFact[n] = modPow(fact[n], MOD - 2, MOD);
        for (int i = n - 1; i >= 0; --i)
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        
        // C(n, 2k) = n! / ((2k)! * (n-2k)!)
        return fact[n] * invFact[2 * k] % MOD * invFact[n - 2 * k] % MOD;
    }

private:
    long long modPow(long long a, long long b, int mod) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
};