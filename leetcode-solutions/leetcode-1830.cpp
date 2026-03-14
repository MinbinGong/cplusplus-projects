/*
 * 1830. Minimum Number of Operations to Make String Sorted
 * 
 * You are given a string s (0-indexed). You are asked to perform the following operation on s until you get a sorted string:
 * 
 * Find the largest index i such that 1 <= i < s.length and s[i] < s[i - 1].
 * Find the largest index j such that i <= j < s.length and s[k] < s[i - 1] for all the possible values of k in the range [i, j] inclusive.
 * Swap the two characters at indices i - 1 and j.
 * Reverse the suffix starting at index i.
 * Return the number of operations needed to make the string sorted. Since the answer can be too large, return it modulo 109 + 7.
 * 
 * Example 1:
 * Input: s = "cba"
 * Output: 5
 * Explanation: The simulation goes as follows:
 * Index i: 0 1 2
 * S: "cba"
 * Swap (1, 2): "cab"
 * 
 * Example 2:
 * Input: s = "aabaa"
 * Output: 2
 * Explanation: The simulation goes as follows:
 * Index i: 0 1 2 3 4
 * S: "aabaa"
 * Swap (0, 3): "baaaa"
 * Reverse suffix starting at 1: "baaaa"
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 3000
 * s consists only of lowercase English letters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int makeStringSorted(string s) {
        const int MOD = 1000000007;
        int n = s.size();
        
        // Precompute factorials and inverse factorials modulo MOD
        vector<long long> fact(n + 1), invFact(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        
        // Fermat's Little Theorem for modular inverse: a^(MOD-2) % MOD
        invFact[n] = powMod(fact[n], MOD - 2, MOD);
        for (int i = n - 1; i >= 0; --i) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }
        
        vector<int> cnt(26, 0);
        long long ans = 0;
        
        // Traverse from right to left
        for (int i = n - 1; i >= 0; --i) {
            int cur = s[i] - 'a';
            // Count characters smaller than s[i] that appear to the right
            for (int smaller = 0; smaller < cur; ++smaller) {
                if (cnt[smaller] == 0) continue;
                
                // Temporarily decrease count of the smaller char
                cnt[smaller]--;
                
                // Calculate number of permutations for the remaining characters (i+1 to n-1)
                long long permutations = fact[n - 1 - i];
                for (int k = 0; k < 26; ++k) {
                    permutations = permutations * invFact[cnt[k]] % MOD;
                }
                
                ans = (ans + permutations) % MOD;
                
                // Restore count
                cnt[smaller]++;
            }
            // Update count for current character
            cnt[cur]++;
        }
        
        return ans;
    }
    
private:
    // Fast modular exponentiation
    long long powMod(long long a, long long b, long long mod) {
        long long res = 1;
        while (b > 0) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
};