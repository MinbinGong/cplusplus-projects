/*
 * Cut Off Trees for Golf Event
 *
 * You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:
 *
 * 0 means the cell cannot be walked through.
 * 1 represents an empty cell that can be walked through.
 * A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
 * In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.
 *
 * You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).
 *
 * Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.
 *
 * You are guaranteed that no two trees have the same height, and there is at least one tree needs to be cut off.
 * 
 * Example 1:
 *
 * Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
 * Output: 6
 * Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
 *
 * Example 2:
 *
 * Input: forest = [[1,2,3],[0,0,0],[7,6,5]]
 * Output: -1
 * Explanation: The trees in the bottom row cannot be accessed as the middle row is blocked.
 *
 * Example 3:
 *
 * Input: forest = [[2,3,4],[0,0,5],[8,7,6]]
 * Output: 6
 * Explanation: You can follow the same path as Example 1 to cut off all the trees.
 * Note that you can cut off the first tree at (0, 0) before making any steps.
 * 
 * Note:
 *
 * The number of nodes in the given tree will be at most 10000.
 * Each node's value is an integer in the range [0, 10^9].
 * 
 */
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size();
        int n = forest[0].size();
        
        // collect all trees (value > 1) with their positions
        vector<tuple<int, int, int>> trees; // (height, x, y)
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (forest[i][j] > 1) {
                    trees.emplace_back(forest[i][j], i, j);
                }
            }
        }
        
        // sort trees by height (ascending)
        sort(trees.begin(), trees.end());
        
        // if there is no tree, we are already done
        if (trees.empty()) return 0;
        
        // starting point (0,0) must be accessible
        if (forest[0][0] == 0) return -1;
        
        int totalSteps = 0;
        int sx = 0, sy = 0;   // current position
        
        for (const auto& tree : trees) {
            int tx = get<1>(tree);
            int ty = get<2>(tree);
            
            // if already at the target tree, no movement needed
            if (sx == tx && sy == ty) continue;
            
            // BFS from (sx, sy) to (tx, ty)
            int steps = bfs(forest, sx, sy, tx, ty);
            if (steps == -1) return -1;   // unreachable tree
            
            totalSteps += steps;
            sx = tx;
            sy = ty;
        }
        
        return totalSteps;
    }
    
private:
    int bfs(const vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        int m = forest.size();
        int n = forest[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        
        dist[sx][sy] = 0;
        q.push({sx, sy});
        
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (x == tx && y == ty) {
                return dist[x][y];
            }
            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                    forest[nx][ny] != 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return -1;   // target not reachable
    }
};