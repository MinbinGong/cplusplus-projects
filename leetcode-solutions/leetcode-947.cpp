/*
 * Most Stones Removed with Same Row or Column
 *
 * On a 2D plane, we place stones at some integer coordinate points.  Each coordinate point may have at most one stone.
 *
 * Now, a move consists of removing a stone that shares a column or row with another stone on the grid.
 *
 * What is the largest possible number of moves we can make?
 *
 * Example 1:
 * Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
 * Output: 5
 * 
 * Example 2:
 * Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
 * Output: 3
 * 
 * Example 3:
 * Input: stones = [[0,0]]
 * Output: 0
 * 
 * Note:
 * 1 <= stones.length <= 1000
 * 0 <= stones[i][j] < 10000
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, int> parent;  // 动态并查集，key 为行号或列号（列号用负数或取反表示）

        // 查找函数（带路径压缩）
        function<int(int)> find = [&](int x) {
            if (!parent.count(x)) parent[x] = x;
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };

        // 合并函数
        auto unite = [&](int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx != ry) parent[rx] = ry;
        };

        // 将每个石头的行和列合并
        for (auto& s : stones) {
            int row = s[0];
            int col = ~s[1];  // 用按位取反得到负数，避免与行号冲突
            unite(row, col);
        }

        // 统计连通分量个数：每个石头所属分量的代表元
        unordered_set<int> components;
        for (auto& s : stones) {
            components.insert(find(s[0]));  // 用行号找代表元即可
        }

        return stones.size() - components.size();
    }
};