/*
 * 1102. Path With Maximum Minimum Value
 * 
 * Given an m x n integer matrix grid, return the maximum score of a path starting at (0, 0) and ending at (m - 1, n - 1) moving in the 4 cardinal directions.
 * 
 * The score of a path is the minimum value in that path.
 * 
 * For example, the score of the path 8 → 4 → 5 → 9 is 4.
 * 
 * 1 <= m, n <= 1000
 * 0 <= grid[i][j] <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution1 {
public:
    int maximumMinimumPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // 方向数组：上、右、下、左
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        // 最大堆：存储(当前路径最小值, x坐标, y坐标)
        priority_queue<tuple<int, int, int>> pq;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        // 从起点开始
        pq.push({grid[0][0], 0, 0});
        visited[0][0] = true;
        
        int result = INT_MAX;
        
        while (!pq.empty()) {
            auto [val, x, y] = pq.top();
            pq.pop();
            
            // 更新当前路径的最小值
            result = min(result, val);
            
            // 如果到达终点，返回结果
            if (x == m - 1 && y == n - 1) {
                return result;
            }
            
            // 探索四个方向
            for (auto& dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                
                // 检查边界和访问状态
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    pq.push({grid[nx][ny], nx, ny});
                }
            }
        }
        
        return result;
    }
};

class Solution2 {
public:
    int maximumMinimumPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int left = 0, right = 1e9;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canReach(grid, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
private:
    bool canReach(vector<vector<int>>& grid, int minVal) {
        int m = grid.size();
        int n = grid[0].size();
        
        if (grid[0][0] < minVal) return false;
        
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push({0, 0});
        visited[0][0] = true;
        
        vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            if (x == m - 1 && y == n - 1) {
                return true;
            }
            
            for (auto& dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                    !visited[nx][ny] && grid[nx][ny] >= minVal) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        
        return false;
    }
};