/*
 * The Maze III
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
 *  You may assume that the ball and the destination are different.
 * 
 */
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        int m = maze.size(), n = maze[0].size();
        // dist[i][j] = minimum distance to (i,j)
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        // path[i][j] = lexicographically smallest path achieving dist[i][j]
        vector<vector<string>> path(m, vector<string>(n, ""));

        // Directions: down, left, right, up (d,l,r,u) ordered by lexicographic? Actually we'll use all but priority queue will handle lex order
        int dirs[4][2] = {{1,0}, {0,-1}, {0,1}, {-1,0}};
        char dirChar[4] = {'d', 'l', 'r', 'u'};

        // Priority queue: (distance, path, x, y)
        using State = tuple<int, string, int, int>;
        auto cmp = [](const State& a, const State& b) {
            int d1 = get<0>(a), d2 = get<0>(b);
            if (d1 != d2) return d1 > d2; // smaller distance first
            return get<1>(a) > get<1>(b); // lexicographically smaller path first
        };
        priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);

        dist[ball[0]][ball[1]] = 0;
        pq.push({0, "", ball[0], ball[1]});

        while (!pq.empty()) {
            auto [curDist, curPath, x, y] = pq.top();
            pq.pop();

            // If current state is not optimal, skip
            if (curDist > dist[x][y] || (curDist == dist[x][y] && curPath > path[x][y]))
                continue;

            // If we reached the hole, return the path (first time is optimal)
            if (x == hole[0] && y == hole[1]) {
                return curPath;
            }

            // Explore four directions
            for (int d = 0; d < 4; ++d) {
                int dx = dirs[d][0], dy = dirs[d][1];
                int nx = x, ny = y;
                int steps = 0;

                // Roll until hit wall or boundary or hole
                while (nx + dx >= 0 && nx + dx < m && ny + dy >= 0 && ny + dy < n &&
                       maze[nx + dx][ny + dy] == 0) {
                    nx += dx;
                    ny += dy;
                    steps++;
                    // If we pass through the hole, stop at hole
                    if (nx == hole[0] && ny == hole[1]) {
                        break;
                    }
                }

                if (steps == 0) continue; // no movement possible

                int newDist = curDist + steps;
                string newPath = curPath + dirChar[d];

                // Update if better
                if (newDist < dist[nx][ny] || (newDist == dist[nx][ny] && newPath < path[nx][ny])) {
                    dist[nx][ny] = newDist;
                    path[nx][ny] = newPath;
                    pq.push({newDist, newPath, nx, ny});
                }
            }
        }

        return "impossible";
    }
};