/**
 * 1135. Connecting Cities With Minimum Cost
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * There are n cities labeled from 1 to n. You are given the integer n and an array connections where connections[i] = [xi, yi, costi] indicates that the cost of connecting city xi and city yi (bidirectional connection) is costi.
 * 
 * Return the minimum cost to connect all the n cities such that there is at least one path between each pair of cities. If it is impossible to connect all the n cities, return -1,
 * 
 * The cost is the sum of the connections' costs used.
 * 
 * Example 1:
 * Input: n = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
 * Output: 6
 * Explanation: 
 * Choosing any 2 edges will connect all cities so we choose the minimum 2.
 * 
 * Example 2:
 * Input: n = 4, connections = [[1,2,3],[3,4,4]]
 * Output: -1
 * Explanation: 
 * There are 4 cities numbered from 1 to 4. It is impossible to connect all cities.
 * 
 * Note:
 * 1 <= n <= 10^4
 * 1 <= connections.length <= 10^4
 * connections[i].length == 3
 * 1 <= xi, yi <= n
 * xi != yi
 * 0 <= costi <= 10^5
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    vector<int> parent, rank;
public:
    int count; // 当前连通分量的数量

    UnionFind(int n) {
        parent.resize(n + 1); // 城市编号从 1 到 n
        rank.resize(n + 1, 0);
        count = n;
        for (int i = 1; i <= n; ++i) {
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

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false; // 已经在同一集合中

        // 按秩合并
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        count--; // 合并后连通分量减一
        return true;
    }
};

class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        // 1. 按照成本升序排序
        sort(connections.begin(), connections.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        UnionFind uf(n);
        int totalCost = 0;
        int edgesUsed = 0;

        // 2. 遍历每条边
        for (const auto& conn : connections) {
            int city1 = conn[0];
            int city2 = conn[1];
            int cost = conn[2];

            // 3. 如果两个城市尚未连通，则选用这条边
            if (uf.unite(city1, city2)) {
                totalCost += cost;
                edgesUsed++;
            }

            // 4. 如果已经选了 n-1 条边，所有城市都已连通
            if (edgesUsed == n - 1) {
                return totalCost;
            }
        }

        // 5. 无法连通所有城市
        return -1;
    }
};