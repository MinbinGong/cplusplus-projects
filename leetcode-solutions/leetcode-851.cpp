/*
 * 851. Loud and Rich
 * 
 * In a group of N people (labelled 0, 1, 2, ..., N-1), each person has different amounts of money, and different levels of quietness.
 * 
 * For convenience, we'll call the person with label x, simply "person x".
 * 
 * We'll say that richer[i] = [x, y] if person x definitely has more money than person y.  Note that richer may only be a subset of valid observations.
 * 
 * Also, we'll say quiet[x] = q if person x has quietness q.
 * 
 * Now, return answer, where answer[x] = y if y is the least quiet person (that is, the person y with the smallest value of quiet[y]), among all people who definitely have equal to or more money than person x.
 * 
 * Example 1:
 * Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
 * Output: [5,5,2,5,4,5,6,7]
 * Explanation: 
 * answer[0] = 5.
 * Person 5 has more money than 3, which has more money than 1, which has more money than 0.
 * The only person who is quieter (has lower quiet[x]) is person 7, but
 * it isn't clear if they have more money than person 0.
 * 
 * Example 2:
 * Input: richer = [], quiet = [0]
 * Output: [0]
 * 
 * Note:
 * 1 <= quiet.length = N <= 500
 * 0 <= quiet[i] < N, all quiet[i] are different.
 * 0 <= richer.length <= N * (N-1) / 2
 * 0 <= richer[i][j] < N
 * richer[i][0] != richer[i][1]
 * richer[i]'s are all different.
 * The observations in richer are all logically consistent.
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> graph(n);
        for (auto& r : richer) {
            // r[0] 比 r[1] 富有，所以从较穷的 r[1] 指向较富的 r[0]
            graph[r[1]].push_back(r[0]);
        }

        vector<int> memo(n, -1); // 记忆化数组，-1表示未计算

        function<int(int)> dfs = [&](int u) -> int {
            if (memo[u] != -1) return memo[u];
            int ans = u; // 自己可能是答案
            for (int v : graph[u]) {
                int cand = dfs(v);
                if (quiet[cand] < quiet[ans]) {
                    ans = cand;
                }
            }
            memo[u] = ans;
            return ans;
        };

        vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = dfs(i);
        }
        return result;
    }
};