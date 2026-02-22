/*
 * Decode Ways II
 * 
 * A message containing letters from A-Z is being encoded to numbers using the following mapping way:
 * 
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * 
 * Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers
 * from 1 to 9.
 * 
 * Given the encoded message containing digits and the character '*', return the total number of ways to decode it.
 * 
 * Also, since the answer may be very large, you should return the output mod 10^9 + 7.
 * 
 * Example 1:
 * Input: "*"
 * Output: 9
 * Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
 * 
 * Example 2:
 * Input: "1*"
 * Output: 9 + 9 = 18
 * 
 * Note:
 * The length of the input string will fit in range [1, 10^5].
 * The input string will only contain the character '*' and digits '0' - '9'.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1; // empty string
        
        for (int i = 1; i <= n; ++i) {
            // decode last single character
            char c = s[i - 1];
            if (c == '*') {
                dp[i] = (dp[i] + dp[i - 1] * 9) % MOD;
            } else if (c != '0') {
                dp[i] = (dp[i] + dp[i - 1]) % MOD;
            }
            
            // decode last two characters
            if (i >= 2) {
                char a = s[i - 2];
                char b = s[i - 1];
                long long ways = 0;
                
                if (a == '0') {
                    ways = 0;
                } else if (a == '1') {
                    if (b == '*') ways = 9;
                    else if (b >= '0' && b <= '9') ways = 1;
                } else if (a == '2') {
                    if (b == '*') ways = 6;
                    else if (b >= '0' && b <= '6') ways = 1;
                } else if (a == '*') {
                    if (b == '*') ways = 15;
                    else if (b >= '0' && b <= '9') {
                        if (b <= '6') ways = 2;
                        else ways = 1;
                    }
                } // else a is '3'..'9' gives 0
                
                dp[i] = (dp[i] + dp[i - 2] * ways) % MOD;
            }
        }
        return dp[n];
    }
};