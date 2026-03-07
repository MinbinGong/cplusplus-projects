/**
 * 1631. Path With Minimum Effort
 * 
 * You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
 * 
 * A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
 * 
 * Example 1:
 * Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
 * Output: 2
 * Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
 * This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
 * 
 * Example 2:
 * Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
 * Output: 1
 * Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].
 * 
 * Example 3:
 * Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
 * Output: 0
 * Explanation: This route does not require any effort.
 * 
 * Constraints:
 * rows == heights.length
 * columns == heights[i].length
 * 1 <= rows, columns <= 100
 * 1 <= heights[i][j] <= 106
 * 
 */
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
        effort[0][0] = 0;
        
        // 方向数组
        vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        // 最小堆，元素为 {当前最大体力消耗, 行, 列}
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0]; // 最小堆
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        pq.push({0, 0, 0});
        
        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            int currEffort = curr[0];
            int row = curr[1];
            int col = curr[2];
            
            // 到达右下角
            if (row == m-1 && col == n-1) {
                return currEffort;
            }
            
            // 如果当前effort已经大于记录的最小值，跳过
            if (currEffort > effort[row][col]) {
                continue;
            }
            
            for (auto& dir : dirs) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
                    int newEffort = max(currEffort, abs(heights[newRow][newCol] - heights[row][col]));
                    if (newEffort < effort[newRow][newCol]) {
                        effort[newRow][newCol] = newEffort;
                        pq.push({newEffort, newRow, newCol});
                    }
                }
            }
        }
        
        return 0;
    }
};