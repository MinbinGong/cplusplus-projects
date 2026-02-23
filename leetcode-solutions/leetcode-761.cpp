/*
 * 761. Special Binary String
 *
 * Special binary strings are binary strings with the following two properties:
 * 
 * The number of 0's is equal to the number of 1's.
 * Every prefix of the binary string has at least as many 1's as 0's.
 * 
 * Given a special string S, a move consists of choosing two consecutive, non-empty, special substrings of S, and swapping them.
 * 
 * (Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.)
 * 
 * At the end of any number of moves, what is the lexicographically largest resulting string possible?
 * 
 * Example 1:
 * Input: S = "11011000"
 * Output: "11100100"
 * Explanation:
 * The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
 * This is the lexicographically largest string possible after some number of swaps.
 * 
 * Note:
 * 1. S has length at most 50.
 * 2. S is guaranteed to be a special binary string as defined above.
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string makeLargestSpecial(string s) {
        // Base case: empty string
        if (s.empty()) return "";

        int n = s.size();
        int balance = 0;
        int start = 0;
        vector<string> topLevel;

        for (int i = 0; i < n; ++i) {
            balance += (s[i] == '1' ? 1 : -1);

            if (balance == 0) {
                // Found a top‑level special substring s[start..i]
                if (start == 0 && i == n - 1) {
                    // The whole string is primitive: process its inner part
                    string inner = s.substr(1, n - 2);
                    return "1" + makeLargestSpecial(inner) + "0";
                } else {
                    // It is a component of a composite special string
                    string sub = s.substr(start, i - start + 1);
                    topLevel.push_back(makeLargestSpecial(sub));
                    start = i + 1;
                }
            }
        }

        // Sort components in descending order (lexicographically largest first)
        sort(topLevel.begin(), topLevel.end(), greater<string>());

        // Concatenate them
        string result;
        for (const string& t : topLevel) {
            result += t;
        }
        return result;
    }
};