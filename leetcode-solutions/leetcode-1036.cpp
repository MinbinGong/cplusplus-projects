/*
 * 1036. Escape a Large Maze
 *
 * In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.
 *
 * We start at the source square and want to reach the target square.  Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.
 *
 * Return true if and only if it is possible to reach the target square through a sequence of moves.
 * 
 * Example 1:
 *
 * Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 * Output: false
 * Explanation: 
 * The target square is inaccessible starting from the source square, because we can't walk outside the grid.
 * 
 * Example 2:
 *
 * Input: blocked = [], source = [0,0], target = [999999,999999]
 * Output: true
 * Explanation: 
 * Because there are no blocked cells, it's possible to reach the target square.
 * 
 * Note:
 * 0 <= blocked.length <= 200
 * blocked[i].length == 2
 * 0 <= blocked[i][j] < 10^6
 * source.length == target.length == 2
 * 0 <= source[i], target[i] < 10^6
 * source != target
 * 
 */
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        // store blocked cells in a hash set
        unordered_set<long long> blocks;
        for (auto& b : blocked) {
            blocks.insert((long long)b[0] * 1000000 + b[1]);
        }

        const int LIMIT = 20000;          // safe bound for maximum enclosed area
        pair<int,int> src = {source[0], source[1]};
        pair<int,int> tgt = {target[0], target[1]};

        int res1 = bfs(src, tgt, blocks, LIMIT);
        if (res1 == 1) return true;       // found target directly

        int res2 = bfs(tgt, src, blocks, LIMIT);
        // both are "free" (visited more than LIMIT cells) → they are in the same infinite component
        return res1 == 2 && res2 == 2;
    }

private:
    // returns: 1 = reached destination, 2 = exceeded limit (free), 0 = trapped
    int bfs(pair<int,int> start, pair<int,int> dest,
            unordered_set<long long>& blocks, int limit) {
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        unordered_set<long long> visited;
        queue<pair<int,int>> q;

        long long startKey = (long long)start.first * 1000000 + start.second;
        visited.insert(startKey);
        q.push(start);

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (x == dest.first && y == dest.second) return 1;

            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 0 || nx >= 1000000 || ny < 0 || ny >= 1000000) continue;

                long long key = (long long)nx * 1000000 + ny;
                if (blocks.count(key) || visited.count(key)) continue;

                // immediate check for destination
                if (nx == dest.first && ny == dest.second) return 1;

                visited.insert(key);
                q.push({nx, ny});
                if (visited.size() > limit) return 2;   // exceeded limit → free
            }
        }
        return 0;   // visited ≤ limit and never reached dest → trapped
    }
};