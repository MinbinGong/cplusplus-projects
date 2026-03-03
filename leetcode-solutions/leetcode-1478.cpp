/**
 * 1478. Allocate Mailboxes
 * 
 * Given the array houses and an integer k. where houses[i] is the location of the ith house along a street, your task is to allocate k mailboxes in the street.
 * 
 * Return the minimum total distance between each house and its nearest mailbox.
 * 
 * The answer is guaranteed to fit in a 32-bit signed integer.
 * 
 * Example 1:
 * 
 * Input: houses = [1,4,8,10,20], k = 3
 * Output: 5
 * Explanation: Allocate mailboxes in position 3, 9 and 20.
 * Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5 
 * 
 * Example 2:
 * 
 * Input: houses = [2,3,5,12,18], k = 2
 * Output: 9
 * Explanation: Allocate mailboxes in position 3 and 14.
 * Minimum total distance from each houses to nearest mailboxes is |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9.
 * 
 * Example 3:
 * 
 * Input: houses = [7,4,6,1], k = 1
 * Output: 8
 * 
 * Example 4:
 * 
 * Input: houses = [3,6,14,10], k = 4
 * Output: 0
 * 
 * Constraints:
 * n == houses.length
 * 1 <= n <= 100
 * 1 <= houses[i] <= 10^4
 * 1 <= k <= n
 * Array houses contain unique integers.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        // 1. 对房子位置进行排序
        sort(houses.begin(), houses.end());

        // 2. 预处理 cost 数组
        // cost[i][j] 表示从房子 i 到 j (闭区间) 放置一个邮筒的最小距离和
        // 使用 n+1 的维度，方便处理索引，1-based 索引
        vector<vector<int>> cost(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                int mid = i + (j - i) / 2; // 中位数的索引 (在 houses 中的索引是 mid-1)
                for (int idx = i; idx <= j; ++idx) {
                    cost[i][j] += abs(houses[idx - 1] - houses[mid - 1]);
                }
            }
        }

        // 3. 动态规划
        // dp[i][t] 表示前 i 个房子放置 t 个邮筒的最小距离和
        // 初始化为一个大数
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX / 2));
        // 边界条件：0 个房子，不管多少个邮筒，距离都是 0
        for (int t = 0; t <= k; ++t) {
            dp[0][t] = 0;
        }

        // 填充 dp 表
        for (int i = 1; i <= n; ++i) {           // 遍历房子数
            for (int t = 1; t <= min(i, k); ++t) { // 遍历邮筒数，不能超过房子数
                // 尝试最后一段的起始点 j
                for (int j = t; j <= i; ++j) {   // 最后一段是从 j 到 i
                    // dp[j-1][t-1] 是前 j-1 个房子用 t-1 个邮筒覆盖
                    // cost[j][i] 是最后一段（j 到 i）用一个邮筒覆盖
                    dp[i][t] = min(dp[i][t], dp[j - 1][t - 1] + cost[j][i]);
                }
            }
        }

        return dp[n][k];
    }
};

class Solution2 {
public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        // 1. 排序
        sort(houses.begin(), houses.end());

        // 2. 预处理 cost 数组 (0-based 索引)
        // cost[i][j] 表示从房子 i 到 j 放置一个邮筒的最小距离和
        vector<vector<int>> cost(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int mid = i + (j - i) / 2;
                // 更高效的计算方式，但为了清晰，这里使用累加
                for (int idx = i; idx <= j; ++idx) {
                    cost[i][j] += abs(houses[idx] - houses[mid]);
                }
                // 也可以利用递推关系优化：cost[i][j] = cost[i][j-1] + houses[j] - houses[mid];
            }
        }

        // 3. 动态规划 (0-based)
        // dp[i][t] 表示前 i+1 个房子 (0..i) 放置 t+1 个邮筒的最小距离和
        vector<vector<int>> dp(n, vector<int>(k, INT_MAX / 2));

        // 初始化：只放 1 个邮筒 (t=0) 的情况
        for (int i = 0; i < n; ++i) {
            dp[i][0] = cost[0][i];
        }

        // 填充 dp 表
        for (int t = 1; t < k; ++t) {            // 邮筒数从 2 到 k (t 是索引，代表 t+1 个)
            for (int i = t; i < n; ++i) {        // 至少需要 t+1 个房子
                for (int j = t - 1; j < i; ++j) { // 最后一段的起始点 j+1
                    // dp[j][t-1] 是前 j+1 个房子用 t 个邮筒 (因为 t-1 索引对应 t 个)
                    // cost[j+1][i] 是最后一段用一个邮筒
                    dp[i][t] = min(dp[i][t], dp[j][t - 1] + cost[j + 1][i]);
                }
            }
        }

        return dp[n - 1][k - 1];
    }
};