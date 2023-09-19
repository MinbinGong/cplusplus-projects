/*
 * Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'
 * where:

    '?' Matches any single character.
    '*' Matches any sequence of characters (including the empty sequence).
    The matching should cover the entire input string (not partial).



    Example 1:

    Input: s = "aa", p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".
    Example 2:

    Input: s = "aa", p = "*"
    Output: true
    Explanation: '*' matches any sequence.
    Example 3:

    Input: s = "cb", p = "?a"
    Output: false
    Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.


    Constraints:

    0 <= s.length, p.length <= 2000
    s contains only lowercase English letters.
    p contains only lowercase English letters, '?' or '*'.
 */
#include <string>
#include <vector>
using namespace std;

bool solvetab(string s, string p) {
    vector<vector<int>> dp(s.length() + 1, vector<int>(p.length() + 1, 0));
    dp[0][0] = true;

    for (int i = 0; i < p.length(); i++) {
        bool flag = true;
        for (int j = 0; j <= i; j++) {
            if (p[j - 1] != '*') {
                flag = false;
                break;
            }
        }
        dp[0][i] = flag;
    }

    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j <= p.length(); j++) {
            if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else {
                dp[i][j] = false;
            }
        }
    }

    return dp[s.length()][p.length()];
}

bool isMatch1(string s, string p) { return solvetab(s, p); }

bool solve(string &str, string &pattern, int i, int j, vector<vector<int>> &dp) {
    if (i < 0 && j < 0) {
        return true;
    }
    if (i >= 0 && j < 0) {
        return false;
    }
    if (j >= 0 && i < 0) {
        for (int k = 0; k <= j; k++) {
            if (pattern[k] != '*') {
                return false;
            }
        }
        return true;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (pattern[j] == '?' || pattern[j] == str[i]) {
        return dp[i][j] = solve(str, pattern, i - 1, j - 1, dp);
    } else if (pattern[j] == '*') {
        return dp[i][j] = solve(str, pattern, i - 1, j, dp) || solve(str, pattern, i, j - 1, dp);
    } else {
        return false;
    }
}

bool isMatch2(string s, string p) {
    vector<vector<int>> dp(s.length(), vector<int>(p.length(), -1));
    return solve(s, p, s.length() - 1, p.length() - 1, dp);
}