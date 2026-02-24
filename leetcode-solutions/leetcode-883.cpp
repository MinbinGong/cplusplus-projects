/**
 * 883. Projection Area of 3D Shapes
 *
 * You are given an n x n grid where we place some 1 x 1 x 1 cubes that are axis-aligned with the x, y, and z axes.
 * Each value v = grid[i][j] represents a tower of v cubes placed on top of the cell (i, j).
 * We view the projection of these cubes onto the xy, yz, and zx planes.
 * A projection is like a shadow, that maps our 3-dimensional figure to a 2-dimensional plane.
 * We are viewing the "shadow" when looking at the cubes from the top, the front, and the side.
 * Return the total area of all three projections.
 *
 * Example 1:
 * Input: grid = [[1,2],[3,4]]
 * Output: 17
 * Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
 *
 * Example 2:
 * Input: grid = [[2]]
 * Output: 5
 *
 * Example 3:
 * Input: grid = [[1,0],[0,2]]
 * Output: 8
 *
 * Note:
 * n == grid.length == grid[i].length
 * 1 <= n <= 50
 * 0 <= grid[i][j] <= 50
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int xy = 0, xz = 0, yz = 0;
        for (int i = 0; i < n; ++i) {
            int maxRow = 0, maxCol = 0;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) xy++;           // 俯视图：每个非零格子贡献1
                maxRow = max(maxRow, grid[i][j]);    // 行最大值（侧视图沿y方向）
                maxCol = max(maxCol, grid[j][i]);    // 列最大值（侧视图沿x方向）
            }
            xz += maxRow;
            yz += maxCol;
        }
        return xy + xz + yz;
    }
};