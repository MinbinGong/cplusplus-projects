/**
 * 864. Shortest Path to Get All Keys
 * 
 * Example 1:
 * Input: ["@.a.#","###.#","b.A.B"]
 * Output: 8
 * 
 * Example 2:
 * Input: ["@..aA","..B#.","....b"]
 * Output: 6
 * 
 * Note:
 * 1 <= grid.length <= 30
 * 1 <= grid[0].length <= 30
 * grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
 * The number of keys is in [1, 6].  Each key has a different letter and opens exactly one lock.
 * 
 */
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size(), n = grid[0].size();
        int start_x, start_y;
        int total_keys = 0;
        // 找到起点并统计钥匙总数
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                char c = grid[i][j];
                if (c == '@') {
                    start_x = i;
                    start_y = j;
                } else if (c >= 'a' && c <= 'f') {
                    total_keys = max(total_keys, c - 'a' + 1);
                }
            }
        }
        int target = (1 << total_keys) - 1;          // 所有钥匙的掩码
        // 访问标记：坐标 (x,y) 和当前钥匙集合 mask
        bool visited[30][30][64] = {false};
        // BFS 队列：元素为 (x, y, mask, distance)
        queue<tuple<int, int, int, int>> q;
        q.emplace(start_x, start_y, 0, 0);
        visited[start_x][start_y][0] = true;

        int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        while (!q.empty()) {
            auto [x, y, mask, dist] = q.front();
            q.pop();

            if (mask == target) return dist;          // 拿到所有钥匙

            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                char c = grid[nx][ny];
                if (c == '#') continue;                // 墙

                int new_mask = mask;
                if (c >= 'a' && c <= 'f') {
                    new_mask |= (1 << (c - 'a'));      // 捡钥匙
                }
                if (c >= 'A' && c <= 'F') {
                    int need = 1 << (c - 'A');
                    if ((mask & need) == 0) continue;  // 没有对应钥匙，锁住
                }
                if (!visited[nx][ny][new_mask]) {
                    visited[nx][ny][new_mask] = true;
                    q.emplace(nx, ny, new_mask, dist + 1);
                }
            }
        }
        return -1;      // 无法拿到所有钥匙
    }
};