/*
 * 803. Bricks Falling When Hit
 *
 * We have a grid of 1s and 0s; the 1s in a cell represent bricks.  A brick will not drop if and only if it is directly connected to the top of the grid, or at least one of its (4-way) adjacent bricks will not drop.
 * 
 * We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j), the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.
 * 
 * Example:
 * Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
 * Output: [2]
 * Explanation: 
 * If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.
 * 
 * Note:
 * The number of rows and columns in the grid will be in the range [1, 200].
 * The number of erasures will not exceed the area of the grid.
 * It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
 * An erasure may refer to a location with no brick - if it does, nothing will happen.
 * 
 */
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> size; // 用于记录连通分量的大小（砖块数量）

public:
    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        // 路径压缩
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并两个节点所在的集合，并返回是否进行了合并操作
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false;
        }
        // 按大小合并，优化树结构
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        return true;
    }

    // 获取节点x所在集合的大小
    int getSize(int x) {
        return size[find(x)];
    }
};

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int rows = grid.size();
        int cols = grid[0].size();
        // 方向数组，用于遍历上下左右四个邻居
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // 1. 复制原始网格，并将所有将被击打的位置的砖块（1）标记为0（消除）
        //    注意：这里不能直接修改grid，因为后续步骤需要用到原始状态来判断某次击打的位置原本是否有砖块
        vector<vector<int>> copy(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                copy[i][j] = grid[i][j];
            }
        }
        for (auto& hit : hits) {
            int x = hit[0], y = hit[1];
            // 如果该位置原本是砖块，则将其消除（置0）
            if (copy[x][y] == 1) {
                copy[x][y] = 0;
            }
        }

        // 2. 初始化并查集。总节点数为 rows * cols + 1，多出的一个节点（索引为 rows * cols）作为虚拟的“天花板”
        int totalNodes = rows * cols;
        int ceiling = totalNodes; // 天花板节点的索引
        UnionFind uf(totalNodes + 1);

        // 3. 根据消除所有击打位置后的网格(copy)来建立初始的连通关系
        //    遍历所有格子，如果是砖块（copy[x][y] == 1），则将其与上、左方向的砖块合并
        //    （注意：只检查上和左可以避免重复合并，因为合并是无向的）
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (copy[i][j] == 1) {
                    int curIndex = i * cols + j;
                    // 如果是第一行的砖块，将其与“天花板”合并
                    if (i == 0) {
                        uf.unite(curIndex, ceiling);
                    }
                    // 检查上方邻居
                    if (i > 0 && copy[i-1][j] == 1) {
                        uf.unite(curIndex, (i-1) * cols + j);
                    }
                    // 检查左方邻居
                    if (j > 0 && copy[i][j-1] == 1) {
                        uf.unite(curIndex, i * cols + (j-1));
                    }
                }
            }
        }

        // 4. 逆向遍历hits数组，逐步添加回砖块，并计算每次添加导致的新增连接到天花板的砖块数量
        vector<int> result(hits.size(), 0);
        for (int k = hits.size() - 1; k >= 0; --k) {
            int x = hits[k][0];
            int y = hits[k][1];

            // 如果原始网格的这个位置没有砖块，那么这次击打不会引起任何变化，直接跳过
            if (grid[x][y] == 0) {
                // result[k] 默认为0
                continue;
            }

            // 记录在添加当前砖块之前，连接到天花板的砖块总数
            int prevCount = uf.getSize(ceiling);

            int curIndex = x * cols + y;
            // 如果当前砖块位于第一行，它应该直接与天花板相连
            if (x == 0) {
                uf.unite(curIndex, ceiling);
            }

            // 检查当前砖块的四个邻居，如果邻居也是砖块（在copy网格中为1），则进行合并
            for (auto& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && copy[nx][ny] == 1) {
                    uf.unite(curIndex, nx * cols + ny);
                }
            }

            // 将当前砖块在copy网格中标记为1（添加回来）
            copy[x][y] = 1;

            // 计算添加当前砖块后，连接到天花板的砖块总数
            int curCount = uf.getSize(ceiling);
            // 新增连接到天花板的砖块数量 = 当前总数 - 之前总数 - 1 (减去当前添加的这块砖本身)
            // 如果计算结果为负数，则取0，表示没有其他砖块因为这次添加而稳定
            result[k] = max(0, curCount - prevCount - 1);
        }

        return result;
    }
};