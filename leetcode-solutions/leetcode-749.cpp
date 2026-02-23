/*
 * 749. Contain Virus
 *
 * A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
 *
 * The world is modeled as an m x n binary grid isInfected, where isInfected[i][j] == 0 represents uninfected cells,
 * and isInfected[i][j] == 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed
 * between any two 4-directionally adjacent cells, on the shared boundary.
 *
 * Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall.
 * Resources are limited. Each day, you can install walls around only one region (i.e., the affected area (continuous
 * block of infected cells) that threatens the most uninfected cells the following night). There will never be a tie.
 *
 * Return the number of walls used to quarantine all the infected regions. If the world will become fully infected,
 * return the number of walls used.
 * 
 * Example 1:
 * 
 * Input: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
 * Output: 10
 * Explanation: There are 2 contaminated regions.
 * On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:
 * 
 * On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
 * 
 * Note:
 * 1. m == isInfected.length
 * 2. n == isInfected[i].length
 * 3. 1 <= m, n <= 50
 * 4. isInfected[i][j] is either 0 or 1.
 * 
 */
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

class Solution {
public:
    int containVirus(vector<vector<int>>& isInfected) {
        int m = isInfected.size();
        int n = isInfected[0].size();
        int ans = 0;
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (true) {
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            vector<vector<pair<int, int>>> components;   // cells of each infected region
            vector<set<pair<int, int>>> frontiers;       // distinct adjacent uninfected cells
            vector<int> walls;                            // number of walls needed to contain the region

            // 1. Find all connected components of infected cells (value == 1)
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {
                        queue<pair<int, int>> q;
                        q.push({i, j});
                        visited[i][j] = true;
                        vector<pair<int, int>> comp;
                        set<pair<int, int>> frontier;
                        int wallCnt = 0;

                        while (!q.empty()) {
                            auto [x, y] = q.front(); q.pop();
                            comp.push_back({x, y});

                            for (auto& d : dirs) {
                                int nx = x + d[0], ny = y + d[1];
                                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

                                if (isInfected[nx][ny] == 1) {
                                    if (!visited[nx][ny]) {
                                        visited[nx][ny] = true;
                                        q.push({nx, ny});
                                    }
                                } else if (isInfected[nx][ny] == 0) {
                                    // uninfected cell -> count wall and record frontier
                                    wallCnt++;
                                    frontier.insert({nx, ny});
                                }
                                // value 2 (contained) is ignored
                            }
                        }

                        components.push_back(comp);
                        frontiers.push_back(frontier);
                        walls.push_back(wallCnt);
                    }
                }
            }

            // No infected regions left
            if (components.empty()) break;

            // 2. Choose the region that threatens the most uninfected cells
            int maxFrontier = -1;
            int idx = -1;
            for (int k = 0; k < frontiers.size(); ++k) {
                if ((int)frontiers[k].size() > maxFrontier) {
                    maxFrontier = frontiers[k].size();
                    idx = k;
                }
            }

            // If no uninfected cell is adjacent to any infected region, stop
            if (maxFrontier == 0) break;

            // 3. Contain the chosen region: add walls and mark as contained (2)
            ans += walls[idx];
            for (auto& p : components[idx]) {
                isInfected[p.first][p.second] = 2;
            }

            // 4. Spread from all other infected regions
            set<pair<int, int>> toInfect;
            for (int k = 0; k < components.size(); ++k) {
                if (k == idx) continue; // skip contained region
                for (auto& p : components[k]) {
                    int x = p.first, y = p.second;
                    for (auto& d : dirs) {
                        int nx = x + d[0], ny = y + d[1];
                        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                        if (isInfected[nx][ny] == 0) {
                            toInfect.insert({nx, ny});
                        }
                    }
                }
            }

            for (auto& p : toInfect) {
                isInfected[p.first][p.second] = 1;
            }
        }

        return ans;
    }
};