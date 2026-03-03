/**
 * 1444. Number of Ways of Cutting a Pizza
 * 
 * Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts. 
 * 
 * For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.
 * 
 * Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.
 * 
 * Example 1:
 * 
 * Input: pizza = ["A..","AAA","..."], k = 3
 * Output: 3 
 * Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
 * 
 * Example 2:
 * 
 * Input: pizza = ["A..","AA.","..."], k = 3
 * Output: 1
 * Explanation: The figure above shows the only way to cut the pizza.
 * 
 * Example 3:
 * 
 * Input: pizza = ["A..","A..","..."], k = 1
 * Output: 1
 * Explanation: The figure above shows the only way to cut the pizza.
 * 
 * Note:
 * 1 <= rows, cols <= 50
 * rows == pizza.length
 * cols == pizza[i].length
 * 1 <= k <= rows * cols
 * pizza consists of characters 'A' and '.' only.
 * 
 */
#include <vector>
#include <string>
#include <functional>
using namespace std;

class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        int n = pizza.size();
        int m = pizza[0].size();
        // prefix sum of apples: pref[i][j] = apples in rectangle [0..i-1][0..j-1]
        vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + (pizza[i][j] == 'A');
            }
        }

        const int MOD = 1e9 + 7;
        // dp[r][c][k] : ways to cut sub‑pizza from (r,c) to bottom‑right into k pieces
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(m, vector<long long>(k + 1, -1)));

        function<long long(int, int, int)> dfs = [&](int r, int c, int kk) -> long long {
            if (kk == 1) {
                int apples = pref[n][m] - pref[r][m] - pref[n][c] + pref[r][c];
                return apples > 0 ? 1 : 0;
            }
            if (dp[r][c][kk] != -1) return dp[r][c][kk];

            long long res = 0;
            // try every horizontal cut
            for (int i = r; i < n - 1; ++i) {
                int topApples = pref[i + 1][m] - pref[r][m] - pref[i + 1][c] + pref[r][c];
                if (topApples == 0) continue;               // top piece must have an apple
                res = (res + dfs(i + 1, c, kk - 1)) % MOD;   // cut bottom part further
            }
            // try every vertical cut
            for (int j = c; j < m - 1; ++j) {
                int leftApples = pref[n][j + 1] - pref[r][j + 1] - pref[n][c] + pref[r][c];
                if (leftApples == 0) continue;               // left piece must have an apple
                res = (res + dfs(r, j + 1, kk - 1)) % MOD;    // cut right part further
            }
            return dp[r][c][kk] = res;
        };

        return dfs(0, 0, k);
    }
};
