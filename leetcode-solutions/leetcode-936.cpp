/*
 * Stamping The Sequence
 *
 * You want to form a target string of lowercase letters.
 *
 * At the beginning, your sequence is target.length '?' marks.  You also have a stamp of lowercase letters.
 *
 * On each turn, you may place the stamp over the sequence, and replace every letter in the sequence with the corresponding letter from the stamp.  You can make up to 10 * target.length turns.
 *
 * For example, if the initial sequence is "?????", and your stamp is "abc",  then you may make "abc??", "?abc?", "??abc" in the first turn.  (Note that the stamp must be fully contained in the boundaries of the sequence in order to stamp.)
 *
 * If the sequence is possible to stamp, then return an array of the index of the left-most letter being stamped at each turn.  If the sequence is not possible to stamp, return an empty array.
 *
 * 
 * Example 1:
 * Input: stamp = "abc", target = "ababc"
 * Output: [0,2]
 * ([1,0,2] would also be accepted as an answer, as well as some other answers.)
 * 
 * Example 2:
 * Input: stamp = "abca", target = "aabcaca"
 * Output: [3,0,1]
 * 
 * Note:
 * 1 <= stamp.length <= target.length <= 1000
 * stamp and target only contain lowercase letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

class Solution1 {
public:
    vector<int> movesToStamp(string stamp, string target) {
        vector<int> res;
        int m = stamp.size(), n = target.size();
        int totalStars = 0;
        vector<bool> visited(n, false); // 标记某个起始位置是否已经操作过

        while (totalStars < n) {
            bool replaced = false;
            // 遍历所有可能的起始位置
            for (int i = 0; i <= n - m; ++i) {
                if (visited[i]) continue; // 已经操作过的位置跳过

                // 检查从 i 开始的子串是否可以揭下印章
                int stars = 0;
                bool match = true;
                for (int j = 0; j < m; ++j) {
                    if (target[i + j] == '*') {
                        stars++; // 已经是星号，说明之前被覆盖过
                    } else if (target[i + j] != stamp[j]) {
                        match = false; // 字符不匹配且不是星号
                        break;
                    }
                }

                if (match && stars < m) { // 找到可以揭下的位置（至少有一个新字符被覆盖）
                    replaced = true;
                    totalStars += (m - stars); // 增加新的星号数量
                    visited[i] = true;
                    res.push_back(i);
                    // 将该子串全部变为 '*'
                    for (int j = 0; j < m; ++j) {
                        target[i + j] = '*';
                    }
                }
            }
            if (!replaced) return {}; // 某次遍历没有找到任何可揭下的位置，说明无法还原
        }

        reverse(res.begin(), res.end()); // 逆向操作顺序反转即为正向盖章顺序
        return res;
    }
};

class Solution2 {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int m = stamp.size(), n = target.size();
        vector<int> indeg(n - m + 1, m); // 每个窗口的入度（初始为 m，表示有 m 个字符待匹配）
        vector<vector<int>> edges(n);      // 邻接表：位置 j 影响了哪些窗口
        queue<int> q;

        // 初始化：构建邻接表和初始入度
        for (int i = 0; i < n - m + 1; ++i) {
            for (int j = 0; j < m; ++j) {
                if (target[i + j] == stamp[j]) {
                    // 字符匹配，该窗口的入度减 1
                    if (--indeg[i] == 0) q.push(i);
                } else {
                    // 字符不匹配，记录依赖关系：位置 i+j 上的字符需要被覆盖
                    edges[i + j].push_back(i);
                }
            }
        }

        vector<bool> seen(n, false); // 标记 target 中的位置是否已经被覆盖成 '*'
        vector<int> ans;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            ans.push_back(cur);

            // 模拟盖章：将当前窗口覆盖的所有位置标记为已覆盖
            for (int i = 0; i < m; ++i) {
                int pos = cur + i;
                if (!seen[pos]) {
                    seen[pos] = true;
                    // 当 pos 位置变成 '*' 后，所有依赖此位置的窗口入度减 1
                    for (int nei : edges[pos]) {
                        if (--indeg[nei] == 0) {
                            q.push(nei);
                        }
                    }
                }
            }
        }

        // 如果所有位置都被覆盖了，则成功
        if (find(seen.begin(), seen.end(), false) == seen.end()) {
            reverse(ans.begin(), ans.end());
            return ans;
        }
        return {};
    }
};