/*
 * 1583. Count Unhappy Friends
 *
 * You are given a list of preferences for n friends, where n is always even.
 * 
 * For each person i, preferences[i] contains a list of friends sorted in the order of preference. In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from 0 to n-1.
 * 
 * All the friends are divided into pairs. The pairings are given in a list pairs, where pairs[i] = [xi, yi] denotes xi is paired with yi and yi is paired with xi.
 * 
 * Example 1:
 * Input: n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
 * Output: 2
 * Explanation:
 * Person 0 prefers person 1 over person 2 and person 3 over person 4.
 * Person 1 prefers person 0 over person 3 and person 2 over person 4.
 * Person 2 prefers person 0 over person 1 and person 3 over person 4.
 * Person 3 prefers person 0 over person 1 and person 2 over person 4.
 * Person 0 and person 1 are happy.
 * Person 2 and person 3 are unhappy.
 * 
 * Constraints:
 * 2 <= n <= 500
 * n is even.
 * preferences.length == n
 * preferences[i].length == n - 1
 * 0 <= preferences[i][j] <= n - 1
 * preferences[i] does not contain i.
 * All the values of preferences[i] are unique.
 * pairs.length == n/2
 * pairs[i].length == 2
 * xi != yi
 * 0 <= xi, yi <= n - 1
 * Each person is contained in exactly one pair.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        // 构建排名矩阵：rank[i][j] 表示朋友 i 对朋友 j 的喜好程度（数值越小越喜欢）
        vector<vector<int>> rank(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int idx = 0; idx < n - 1; ++idx) {
                int j = preferences[i][idx];
                rank[i][j] = idx;   // idx 越小越喜欢
            }
        }

        // 记录每个朋友的配对伙伴
        vector<int> partner(n, -1);
        for (auto& p : pairs) {
            int x = p[0], y = p[1];
            partner[x] = y;
            partner[y] = x;
        }

        vector<bool> unhappy(n, false);

        // 检查每个朋友 i 是否不开心
        for (int i = 0; i < n; ++i) {
            int j = partner[i];                // i 的配对对象
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                int l = partner[k];            // k 的配对对象
                // 条件：i 更喜欢 k 而不是 j，且 k 更喜欢 i 而不是 l
                if (rank[i][k] < rank[i][j] && rank[k][i] < rank[k][l]) {
                    unhappy[i] = true;
                    break;                      // 一旦发现 i 不开心即可跳出
                }
            }
        }

        // 统计不开心的朋友个数
        int ans = 0;
        for (bool b : unhappy) {
            if (b) ans++;
        }
        return ans;
    }
};