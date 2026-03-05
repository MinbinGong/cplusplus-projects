/**
 * 1591. Strange Printer II
 * 
 * There is a strange printer with the following two special properties:
 * 
 * The printer can only print a sequence of the same character each time.
 * At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.
 * Given a string s, return true if it is possible to print the string from the strange printer, otherwise return false.
 * 
 * Example 1:
 * Input: s = "aaabbb"
 * Output: true
 * Explanation: Print "aaa" first and then print "bbb".
 * 
 * Example 2:
 * Input: s = "aba"
 * Output: false
 * Explanation: It is impossible to print "aba" because the printer can only print sequences of the same character.
 * 
 * Constraints:
 * 1 <= s.length <= 100
 * s consists of lowercase English letters.
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        
        // 记录每种颜色的最小/最大行、最小/最大列
        unordered_map<int, vector<int>> bounds; // [minR, maxR, minC, maxC]
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = targetGrid[i][j];
                if (!bounds.count(c)) {
                    bounds[c] = {i, i, j, j};
                } else {
                    auto& b = bounds[c];
                    b[0] = min(b[0], i);
                    b[1] = max(b[1], i);
                    b[2] = min(b[2], j);
                    b[3] = max(b[3], j);
                }
            }
        }
        
        // 将颜色映射到索引
        vector<int> colors;
        for (auto& p : bounds) colors.push_back(p.first);
        int k = colors.size();
        unordered_map<int, int> idx;
        for (int i = 0; i < k; ++i) idx[colors[i]] = i;
        
        // 构建依赖图
        vector<vector<bool>> adj(k, vector<bool>(k, false));
        vector<int> indeg(k, 0);
        
        for (int ci = 0; ci < k; ++ci) {
            int c = colors[ci];
            auto& b = bounds[c];
            int r1 = b[0], r2 = b[1], c1 = b[2], c2 = b[3];
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    int d = targetGrid[i][j];
                    if (d != c) {
                        int di = idx[d];
                        if (!adj[ci][di]) {
                            adj[ci][di] = true;
                            indeg[di]++;
                        }
                    }
                }
            }
        }
        
        // 拓扑排序
        queue<int> q;
        for (int i = 0; i < k; ++i) {
            if (indeg[i] == 0) q.push(i);
        }
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cnt++;
            for (int v = 0; v < k; ++v) {
                if (adj[u][v]) {
                    indeg[v]--;
                    if (indeg[v] == 0) q.push(v);
                }
            }
        }
        return cnt == k;
    }
};