/*
 * Distinct Subsequences
 *
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.
 * The test cases are generated so that the answer fits on a 32-bit signed integer.
 */
#include <vector>
#include <string>
using namespace std;

int solveRecursive(int i, int j, string s, string t) {
    if (j < 0) {
        return 1;
    }

    if (i < 0) {
        return 0;
    }

    if (s[i] == t[j]) {
        return solveRecursive(i - 1, j - 1, s, t) + solveRecursive(i - 1, j, s, t);
    }

    return solveRecursive(i - 1, j, s, t);
}
int numDistinctRecursive(string s, string t) {
    int n = s.size();
    int m = t.size();
    
    return solveRecursive(n - 1, m - 1, s, t);
}

int solveMemorization(int i, int j, string s, string t, vector<vector<int>> &dp) {
    if (j < 0) {
        return 1;
    }

    if (i < 0) {
        return 0;
    }

    if (s[i] == t[j]) {
        return dp[i][j] = solveMemorization(i - 1, j - 1, s, t, dp) + solveMemorization(i - 1, j, s, t, dp);
    }

    return dp[i][j] = solveMemorization(i - 1, j, s, t, dp);
}

int numDistinctMemorization(string s, string t) {
    int n = s.size();
    int m = t.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemorization(n - 1, m - 1, s, t, dp);
}

int solve(int i, int j, string s, string t, vector<vector<int>> &dp) {
    if (j == 0) {
        return 1;
    }

    if (i == 0) {
        return 0;
    }

    if (dp[i][j] != -1) return dp[i][j];

    if (s[i - 1] == t[j - 1]) {
        return dp[i][j]= solve(i - 1, j - 1, s, t, dp) + solve(i - 1, j, s, t, dp);
    }

    return dp[i][j]= solve(i - 1, j, s, t, dp);
}

int numDistinct(string s, string t) {
    int n = s.size();
    int m = t.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return solve(n, m, s, t, dp);
}

int numDistinctTabulation(string s, string t) {
    int n = s.size();
    int m = t.size();

    vector<vector<double>> dp(n + 1, vector<double>(m + 1, 0));
    
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }


    for (int i = 0; i <= m; ++i) {
        dp[0][i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return (int)dp[n][m];
}

int numDistinctSpaceOptimization1(string s, string t) {
    int n = s.size();
    int m = t.size();

    vector<double> prev(m + 1, 0);
    vector<double> curr(m + 1, 0);

    prev[0] = curr[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1]) {
                curr[j] = prev[j - 1] + prev[j];
            } else {
                curr[j] = prev[j];
            }
        }

        prev = curr;
    }

    return (int) prev[m];
}

int numDistinctSpaceOptimization2(string s, string t) {
    int n = s.size();
    int m = t.size();

    vector<double> prev(m + 1, 0);

    prev[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= ; --j) {
            if (s[i - 1] == t[j - 1]) {
                prev[j] = prev[j - 1] + prev[j];
            }
        }
    }

    return (int)prev[m];
}


