/**
 * 1259. Handshakes That Don't Cross
 * 
 * n people shake hands exactly once.
 * 
 * Return the number of ways these handshakes could occur such that none of the handshakes cross.
 * 
 * Since this number could be very big, return the answer mod 10^9 + 7.
 * 
 * n is even.
 * 
 * Example 1:
 * Input: n = 4
 * Output: 2
 * Explanation: There are two ways to do it, the first way is [(1,2),(3,4)] and the second one is [(2,3),(4,1)].
 * 
 * Example 2:
 * Input: n = 6
 * Output: 5
 * Explanation: There are five ways to do it, the first way is [(1,2),(3,4),(5,6)], the second way is [(1,2),(4,5),(6,3)], the third way is [(1,3),(2,4),(5,6)], the fourth way is [(1,4),(2,3),(5,6)], and the fifth way is [(1,5),(2,4),(3,6)].
 * 
 * Note:
 * 2 <= n <= 1000
 * n is even.
 * 
 */
#include <vector>

class Solution {
public:
    int numberOfWays(int numPeople) {
        const int MOD = 1e9 + 7;
        int n = numPeople / 2;  // number of handshake pairs = Catalan index
        std::vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] = (dp[i] + dp[j] * dp[i - 1 - j]) % MOD;
            }
        }
        return static_cast<int>(dp[n]);
    }
};