/*
 * Squirrel Simulation
 *
 * You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server.
 * Two servers are said to communicate if they are on the same row or on the same column.
 * 
 * You need to return the number of servers that communicate with any other server.
 * 
 * Example:
 * Input: grid = [[1,0],[0,1]]
 * Output: 0
 * Explanation: No servers can communicate with others.
 * 
 * Input: grid = [[1,0],[1,1]]
 * Output: 3
 * Explanation: All three servers can communicate with at least one other server.
 * 
 * Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
 * Output: 4
 * Explanation: The two servers in the first row can communicate with each other. The two servers in the third column can communicate with each other. The server at right bottom corner can't communicate with any other server.
 * 
 * Note:
 * m == grid.length
 * n == grid[0].length
 * 1 <= m <= 250
 * 1 <= n <= 250
 * grid[i][j] == 0 or 1
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts) {
        // 计算所有坚果到树的距离之和 (用于后面的 totalDist)
        int totalDist = 0;
        for (const auto& nut : nuts) {
            totalDist += distance(nut, tree) * 2;
        }

        int minTotal = INT_MAX;
        // 遍历每个坚果，假设它是第一个被捡的
        for (const auto& nut : nuts) {
            int nutToTree = distance(nut, tree);
            int squirrelToNut = distance(nut, squirrel);
            // 计算以此为第一个坚果的总路程
            int currentDist = totalDist - nutToTree + squirrelToNut;
            minTotal = min(minTotal, currentDist);
        }

        return minTotal;
    }

private:
    // 计算曼哈顿距离的辅助函数
    int distance(const vector<int>& a, const vector<int>& b) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
};