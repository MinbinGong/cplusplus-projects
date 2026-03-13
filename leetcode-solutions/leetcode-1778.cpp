/**
 * 1778. Shortest Path in a Hidden Grid
 * 
 * Grid is a hidden grid that is connected to the bottom-right cell (m-1, n-1) of the grid. You are initially at the top-left cell (0, 0).
 * 
 * You want to reach the bottom-right cell (m-1, n-1). On each step, you can move up, down, left, or right.
 * 
 * You are given a 2D array grid of size m x n, where grid[i][j] is either 0 (meaning the cell is empty) or 1 (meaning the cell is blocked).
 * 
 * Return the length of the shortest path from (0, 0) to (m-1, n-1). If no such path exists, return -1.
 * 
 * Example 1:
 * 
 * Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
 * Output: 4
 * Explanation: The shortest path is shown.
 * 
 * Example 2:
 * 
 * Input: grid = [[0,0,0],[1,1,1],[1,1,0]]
 * Output: -1
 * Explanation: There is no path from (0, 0) to (2, 2).
 * 
 * Constraints:
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 100
 * grid[i][j] is either 0 or 1.
 * grid[0][0] == grid[m-1][n-1] == 0
 * 
 */
/**
 * // 这是 GridMaster 的 API 接口，在题目中已定义，我们无需实现。
 * // 你需要通过这个对象与隐藏的网格交互。
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     bool isTarget();
 * };
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
private:
    // 用 pair<int, int> 存储坐标 (x, y)
    using Coord = pair<int, int>;
    // 方向映射：U, R, D, L 分别对应坐标变化
    const vector<char> dirs = {'U', 'R', 'D', 'L'};
    const int dx[4] = {-1, 0, 1, 0}; // 对应 U, R, D, L 的x变化
    const int dy[4] = {0, 1, 0, -1}; // 对应 U, R, D, L 的y变化
    // 反向方向映射，用于回溯
    const char opposite[4] = {'D', 'L', 'U', 'R'};

    unordered_set<Coord, hash<Coord>> accessible; // 存储所有可达格子的坐标
    Coord target = {-1, -1}; // 目标格子坐标，初始化为无效值

    // 自定义pair哈希函数，以便在unordered_set中使用
    struct hash_pair {
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };

    // DFS探索网格
    void dfs(Coord cur, GridMaster& master) {
        int x = cur.first, y = cur.second;

        // 检查当前格子是否是目标
        if (master.isTarget()) {
            target = cur;
        }

        // 尝试四个方向
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            Coord next = {nx, ny};

            // 如果可以移动且没有访问过
            if (master.canMove(dirs[i]) && accessible.find(next) == accessible.end()) {
                // 标记为已访问（将探索）
                accessible.insert(next);
                // 移动到下一个格子
                master.move(dirs[i]);
                // 递归探索
                dfs(next, master);
                // 回溯：回到原来的格子
                master.move(opposite[i]);
            }
        }
    }

public:
    int findShortestPath(GridMaster& master) {
        accessible.clear();
        target = {-1, -1};

        Coord start = {0, 0};
        accessible.insert(start);
        // 步骤1：DFS探索，构建地图
        dfs(start, master);

        // 如果没有找到目标，返回-1
        if (target.first == -1 && target.second == -1) {
            return -1;
        }

        // 步骤2：BFS寻找最短路径
        queue<Coord> q;
        unordered_set<Coord, hash_pair> visited; // 记录BFS中已访问的格子
        q.push(start);
        visited.insert(start);
        int steps = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            // 逐层遍历
            for (int i = 0; i < levelSize; ++i) {
                Coord cur = q.front(); q.pop();
                int x = cur.first, y = cur.second;

                // 到达目标
                if (cur == target) {
                    return steps;
                }

                // 检查四个邻居
                for (int j = 0; j < 4; ++j) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    Coord neighbor = {nx, ny};

                    // 如果邻居是可达的，且在BFS中未被访问过
                    if (accessible.find(neighbor) != accessible.end() && 
                        visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            steps++;
        }

        // 理论上，如果DFS能到达目标，BFS一定能找到，但为了完整性返回-1
        return -1;
    }
};