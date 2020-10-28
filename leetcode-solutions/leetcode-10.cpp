/*
 * Regular Expression Matching
 * Given an input string (s) and a pattern (p), implement regular expression
 * matching with support for '.' and '*' where: 
 * 
 * 1.'.' Matches any single character.​​​​
 * 2.'*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 */
#include <string>
#include <vector>
using namespace std;

bool isMatch(string s, string p)
{
    int n = s.length();
    int m = p.length();
    if (n == 0 && m == 0)
    {
        return true;
    }

    if (m == 0)
    {
        return false;
    }

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;
    for (size_t j = 2; j <= m; ++j)
    {
        dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
    }

    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= m; ++j)
        {
            if (p[j - 1] >= 'a' && p[j - 1] <= 'z')
            {
                dp[i][j] = dp[i - 1][j - 1] && (bool)(s[i - 1] == p[j - 1]);
            }
            else if (p[j - 1] == '.')
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (j > 1)
            {
                if (s[i - 1] == p[j - 2] || p[j - 2] == '.')
                {
                    dp[i][j] = dp[i - 1][j] | dp[i][j - 2];
                }
                else
                {
                    dp[i][j] = dp[i][j - 2];
                }
            }
        }
    }
    return dp[n][m];
}