/**
 * 1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
 * 
 * Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbours of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighbours if they share one edge.
 * 
 * Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
 * 
 * Binary matrix is a matrix with all cells equal to 0 or 1 only.
 * 
 * Zero matrix is a matrix with all cells equal to 0.
 * 
 * Example 1:
 * Input: mat = [[0,0],[0,1]]
 * Output: 3
 * Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
 * 
 * Example 2:
 * Input: mat = [[0]]
 * Output: 0
 * 
 * Example 3:
 * Input: mat = [[1,1,1],[1,0,1],[0,0,0]]
 * Output: 6
 * 
 * Example 4:
 * Input: mat = [[1,0,0],[1,0,0]]
 * Output: -1
 * 
 * Note:
 * 1 <= m <= 3
 * 1 <= n <= 3
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int total = m * n;
        int start = 0;
        // encode initial matrix as a bitmask
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) {
                    start |= (1 << (i * n + j));
                }
            }
        }
        if (start == 0) return 0;

        // precompute flip masks for each cell (cell and its neighbours)
        vector<int> flipMask(total, 0);
        int dirs[5][2] = {{0,0}, {1,0}, {-1,0}, {0,1}, {0,-1}};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int idx = i * n + j;
                for (auto& d : dirs) {
                    int ni = i + d[0], nj = j + d[1];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        flipMask[idx] |= (1 << (ni * n + nj));
                    }
                }
            }
        }

        // BFS over all 2^(m*n) states
        vector<int> dist(1 << total, -1);
        dist[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            int d = dist[cur];
            for (int cell = 0; cell < total; ++cell) {
                int nxt = cur ^ flipMask[cell];
                if (dist[nxt] == -1) {
                    dist[nxt] = d + 1;
                    if (nxt == 0) return dist[nxt];
                    q.push(nxt);
                }
            }
        }
        return -1;
    }
};
