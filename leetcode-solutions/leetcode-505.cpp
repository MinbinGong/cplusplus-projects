/*
 * The Maze II
 *
 *  There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through the empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
 *
 *  Given the m x n maze, the ball's start position and the destination, where start = [startrow, startcol] and destination = [destinationrow, destinationcol], return the shortest distance for the ball to stop at the destination. If the ball cannot stop at destination, return -1.
 *
 *  The distance is the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included).
 *
 *  You may assume that the borders of the maze are all walls (see examples).
 *
 *  Constraints:
 *  m == maze.length
 *  n == maze[i].length
 *  1 <= m, n <= 100
 *  maze[i][j] is 0 or 1.
 *  start.length == 2
 *  destination.length == 2
 *  0 <= startrow, destinationrow <= m
 *  0 <= startcol, destinationcol <= n
 *  Both the ball and the destination exist in an empty space, and they will not be in the same position initially.
 *  The maze contains at least 2 empty spaces.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[start[0]][start[1]] = 0;

        // 优先队列存储 (距离, x, y)，按距离升序
        using State = tuple<int, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;
        pq.emplace(0, start[0], start[1]);

        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!pq.empty()) {
            auto [d, x, y] = pq.top();
            pq.pop();

            // 如果当前距离已不是最优，跳过
            if (d > dist[x][y]) continue;
            // 到达终点时即可返回（因为优先队列保证当前距离最小）
            if (x == destination[0] && y == destination[1]) return d;

            for (auto [dx, dy] : dirs) {
                int nx = x, ny = y;
                int steps = 0;
                // 沿方向滚动直到遇到墙或边界
                while (nx + dx >= 0 && nx + dx < m && ny + dy >= 0 && ny + dy < n &&
                       maze[nx + dx][ny + dy] == 0) {
                    nx += dx;
                    ny += dy;
                    steps++;
                }
                if (steps == 0) continue; // 无法移动

                int newDist = d + steps;
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    pq.emplace(newDist, nx, ny);
                }
            }
        }
        return -1; // 不可达
    }
};