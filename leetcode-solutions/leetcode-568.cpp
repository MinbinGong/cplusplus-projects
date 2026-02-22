/*
 * Maximum Vacation Days
 *
 * Given N cities and M flights, find the maximum number of vacation days you can take.
 * 
 * You can only fly from a city to another city if there is a flight between them.
 * 
 * Example:
 * Input: N = 2, flights = [[0,1,1],[1,0,1],[1,1,0]], days = [[1,3],[2,2]]
 * Output: 4
 * Explanation:
 * You can fly from city 0 to city 1 on week 0, week 1, and week 2.
 * You can fly from city 1 to city 0 on week 3, and week 4.
 * You can take a maximum of 4 days of vacation.
 * 
 * Note:
 * The number of cities N will be in the range [1, 100].
 * The number of flights M will be in the range [0, N * (N - 1) / 2].
 * The number of weeks K will be in the range [1, 100].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size();          // 城市数量
        int K = days[0].size();          // 周数
        
        // dp[week][city]：第 week 周结束时在 city 的最大休假天数
        vector<vector<int>> dp(K, vector<int>(n, INT_MIN));
        
        // 第 0 周初始化
        for (int j = 0; j < n; ++j) {
            if (j == 0 || flights[0][j] == 1) {
                dp[0][j] = days[j][0];
            }
        }
        
        // 从第 1 周到第 K-1 周
        for (int week = 1; week < K; ++week) {
            for (int j = 0; j < n; ++j) {                // 本周所在城市 j
                for (int i = 0; i < n; ++i) {            // 上周所在城市 i
                    if (dp[week-1][i] != INT_MIN && (i == j || flights[i][j] == 1)) {
                        dp[week][j] = max(dp[week][j], dp[week-1][i] + days[j][week]);
                    }
                }
            }
        }
        
        // 答案：最后一周的最大值
        return *max_element(dp[K-1].begin(), dp[K-1].end());
    }
};

int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
    int n = flights.size(), K = days[0].size();
    vector<int> dp(n, INT_MIN);
    for (int j = 0; j < n; ++j) {
        if (j == 0 || flights[0][j] == 1) dp[j] = days[j][0];
    }
    for (int week = 1; week < K; ++week) {
        vector<int> next(n, INT_MIN);
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                if (dp[i] != INT_MIN && (i == j || flights[i][j] == 1)) {
                    next[j] = max(next[j], dp[i] + days[j][week]);
                }
            }
        }
        dp = move(next);
    }
    return *max_element(dp.begin(), dp.end());
}