/*
 * Shortest Distance from All Buildings
 *
 * You are given an m x n grid grid of values 0, 1, or 2, where:
 * 
 * each 0 marks an empty land that you can pass by freely,
 * each 1 marks a building that you cannot pass through, and
 * each 2 marks an obstacle that you cannot pass through.
 * You want to build a house on an empty land that reaches all buildings in the shortest total travel distance.
 * You can only move up, down, left, and right.
 * 
 * Return the shortest travel distance for such a house.
 * If it is not possible to build such a house according to the above rules, return -1.
 * 
 * The total travel distance is the sum of the distances between the houses of the friends and the meeting point.
 * 
 * The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.
 * 
 * Example 1:
 * Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
 * Output: 7
 * Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
 * The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
 * So return 7.
 * 
 * Example 2:
 * Input: grid = [[1,0]]
 * Output: 1
 * 
 * Example 3:
 * Input: grid = [[1]]
 * Output: -1
 *
 */
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int rows = grid.size();
        if (rows == 0) return -1;
        int cols = grid[0].size();
        
        // 记录每个空地可达的建筑物数量
        vector<vector<int>> reach(rows, vector<int>(cols, 0));
        // 记录每个空地到所有建筑物的距离总和
        vector<vector<int>> dist(rows, vector<int>(cols, 0));
        
        int totalBuildings = 0;
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // 从每一个建筑物出发进行BFS
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    totalBuildings++;
                    // BFS队列，存储坐标和当前距离
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    
                    // 记录当前BFS中已访问的位置，避免重复
                    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
                    visited[i][j] = true;
                    
                    int level = 0;
                    while (!q.empty()) {
                        int size = q.size();
                        level++;  // 每向外一层，距离+1
                        
                        for (int k = 0; k < size; ++k) {
                            auto [x, y] = q.front();
                            q.pop();
                            
                            for (auto& d : dirs) {
                                int nx = x + d[0];
                                int ny = y + d[1];
                                
                                // 边界检查、空地检查、未访问检查
                                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                                    grid[nx][ny] == 0 && !visited[nx][ny]) {
                                    
                                    reach[nx][ny]++;          // 空地可达建筑物数量+1
                                    dist[nx][ny] += level;    // 累加距离
                                    visited[nx][ny] = true;
                                    q.push({nx, ny});
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // 寻找最优空地：所有建筑物都能到达，且总距离最小
        int ans = INT_MAX;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0 && reach[i][j] == totalBuildings) {
                    ans = min(ans, dist[i][j]);
                }
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};