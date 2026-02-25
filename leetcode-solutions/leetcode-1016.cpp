/*
 * 1016. Binary String With Substrings Representing 1 To N
 *
 * Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N, return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.
 * 
 * Example 1:
 *
 * Input: S = "0110", N = 3
 * Output: true
 * 
 * Example 2:
 *
 * Input: S = "0110", N = 4
 * Output: false
 * 
 * Note:
 *
 * 1 <= S.length <= 1000
 * 1 <= N <= 10^9
 * 
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool queryString(string S, int N) {
        int L = S.size();
        // Maximum number of distinct substrings is L*(L+1)/2.
        // If N exceeds that, we cannot cover all numbers 1..N.
        if (N > L * (L + 1) / 2) return false;

        vector<bool> seen(N + 1, false);

        for (int i = 0; i < L; ++i) {
            if (S[i] == '0') continue;          // binary numbers have no leading zeros
            long long num = 0;
            for (int j = i; j < L; ++j) {
                num = num * 2 + (S[j] - '0');
                if (num > N) break;              // further digits only increase the number
                if (num >= 1) seen[num] = true;
            }
        }

        for (int x = 1; x <= N; ++x) {
            if (!seen[x]) return false;
        }
        return true;
    }
};