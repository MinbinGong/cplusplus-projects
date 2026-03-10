/**
 * 1733. Minimum Number of People to Teach
 * 
 * On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.
 * You are given an integer n, an array languages, and an array friendships where:
 * languages[i] is a list of languages the ith user knows, and
 * friendships[i] = [ui, vi] denotes a friendship between the users ui and vi.
 * You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.
 * Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.
 * 
 * Example 1:
 * Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
 * Output: 1
 * Explanation: You can either teach user 1 the second language or user 2 the first language.
 * 
 * Example 2:
 * Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
 * Output: 2
 * Explanation: Teach the third language to users 1 and 3, yielding two users to teach.
 * 
 * Constraints:
 * m == languages.length
 * n == languages[i].length
 * 1 <= m <= 500
 * 1 <= n <= 500
 * 1 <= languages[i][j] <= n
 * 1 <= ui, vi <= m
 * ui != vi
 * All values in languages[i] are unique.
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size(); // 人数，编号从1到m
        // 将每个人的语言列表转为集合，方便快速查找
        vector<unordered_set<int>> langSets(m + 1);
        for (int i = 0; i < m; ++i) {
            for (int lang : languages[i]) {
                langSets[i + 1].insert(lang);
            }
        }

        // 找出所有没有共同语言的朋友对
        vector<pair<int, int>> needPairs;
        for (auto& f : friendships) {
            int u = f[0], v = f[1];
            bool common = false;
            for (int lang : langSets[u]) {
                if (langSets[v].count(lang)) {
                    common = true;
                    break;
                }
            }
            if (!common) {
                needPairs.push_back({u, v});
            }
        }

        if (needPairs.empty()) return 0; // 所有朋友对已有共同语言

        int ans = INT_MAX;

        // 枚举要教的语言
        for (int lang = 1; lang <= n; ++lang) {
            // 标记每个人是否原本就会这种语言
            vector<bool> knows(m + 1, false);
            for (int i = 1; i <= m; ++i) {
                if (langSets[i].count(lang)) knows[i] = true;
            }

            // 筛选出需要被覆盖的边：两端都不会该语言
            vector<pair<int, int>> edges;
            for (auto& p : needPairs) {
                int u = p.first, v = p.second;
                if (!knows[u] && !knows[v]) {
                    edges.push_back({u, v});
                }
            }

            if (edges.empty()) {
                ans = min(ans, 0);
                continue;
            }

            // 贪心求最小点覆盖
            vector<bool> covered(edges.size(), false);
            vector<bool> learned(m + 1, false); // 标记是否被教
            int cnt = 0;

            while (true) {
                // 统计每个未学的人当前能覆盖的未覆盖边数
                vector<int> coverCount(m + 1, 0);
                for (int i = 0; i < edges.size(); ++i) {
                    if (!covered[i]) {
                        auto [u, v] = edges[i];
                        if (!learned[u]) coverCount[u]++;
                        if (!learned[v]) coverCount[v]++;
                    }
                }

                // 选一个能覆盖最多未覆盖边的人（且不会该语言，且未被教）
                int best = 0, bestPerson = -1;
                for (int i = 1; i <= m; ++i) {
                    if (!knows[i] && !learned[i] && coverCount[i] > best) {
                        best = coverCount[i];
                        bestPerson = i;
                    }
                }

                if (bestPerson == -1) break; // 没有可选的，理论上不应发生

                // 教这个人
                learned[bestPerson] = true;
                cnt++;

                // 覆盖所有与他相关的边
                for (int i = 0; i < edges.size(); ++i) {
                    if (!covered[i]) {
                        auto [u, v] = edges[i];
                        if (u == bestPerson || v == bestPerson) {
                            covered[i] = true;
                        }
                    }
                }

                // 检查是否全部覆盖
                bool allCovered = true;
                for (bool c : covered) {
                    if (!c) { allCovered = false; break; }
                }
                if (allCovered) break;
            }

            ans = min(ans, cnt);
        }

        return ans;
    }
};