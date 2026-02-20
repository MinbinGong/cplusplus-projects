/*
 * Walls and Gates
 * 
 * You are given a m x n 2D grid initialized with these three possible values.
 * -1 - A wall or an obstacle.
 * 0 - A gate.
 * INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
 * Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
 * 
 * Example:
 * 
 * Given the 2D grid:
 * 
 * INF  -1  0  INF
 * INF INF INF  -1
 * INF  -1 INF  -1
 *   0  -1 INF INF
 * After running your function, the 2D grid should be:
 * 
 *   3  -1   0   1
 *   2   2   1  -1
 *   1  -1   2  -1
 *   0  -1   3   4
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        
        const int INF = 2147483647;
        int m = rooms.size();
        int n = rooms[0].size();
        vector<pair<int, int>> directions = {{1,0}, {0,1}, {-1,0}, {0,-1}};
        queue<pair<int, int>> q;
        
        // 第一步：将所有门的坐标加入队列
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rooms[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        // 第二步：BFS 逐层扩散
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            int distance = rooms[x][y] + 1;
            
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                // 只处理合法的空房间
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && rooms[nx][ny] == INF) {
                    rooms[nx][ny] = distance;
                    q.push({nx, ny});
                }
            }
        }
    }
};