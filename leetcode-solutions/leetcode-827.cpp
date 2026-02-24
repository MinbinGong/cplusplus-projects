/**
 * 827. Making A Large Island
 *
 * In a 2D grid of 0s and 1s, we change at most one 0 to a 1.
 *
 * After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).
 *
 * Example:
 * Input: [[1, 0], [0, 1]]
 * Output: 3
 * Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
 *
 * Input: [[1, 1], [1, 0]]
 * Output: 4
 * Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
 *
 * Input: [[1, 1], [1, 1]]
 * Output: 4
 * Explanation: Can't change any 0 to 1, only one island with area = 4.
 *
 * Notes:
 * 1 <= grid.length = grid[0].length <= 50.
 * 0 <= grid[i][j] <= 1.
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();
        vector<vector<int>> id(n, vector<int>(m, -1));
        unordered_map<int, int> area; // island ID -> area
        int curId = 0;
        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

        // DFS to label each island and compute area
        function<void(int,int,int)> dfs = [&](int x, int y, int islandId) {
            id[x][y] = islandId;
            area[islandId]++;
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && id[nx][ny] == -1) {
                    dfs(nx, ny, islandId);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1 && id[i][j] == -1) {
                    dfs(i, j, curId);
                    curId++;
                }
            }
        }

        // If there are no zeros, answer is area of the only island (or 0 if all zeros)
        int maxArea = 0;
        for (auto& p : area) maxArea = max(maxArea, p.second);

        // Try each zero cell
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 0) {
                    unordered_set<int> neighbors;
                    int total = 1; // change this zero to one
                    for (auto& d : dirs) {
                        int ni = i + d[0], nj = j + d[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == 1) {
                            int islandId = id[ni][nj];
                            if (neighbors.find(islandId) == neighbors.end()) {
                                neighbors.insert(islandId);
                                total += area[islandId];
                            }
                        }
                    }
                    maxArea = max(maxArea, total);
                }
            }
        }

        return maxArea;
    }
};