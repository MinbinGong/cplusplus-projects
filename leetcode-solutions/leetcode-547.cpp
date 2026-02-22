/*
 * Number of Provinces
 *
 * There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
 * A province is a group of directly or indirectly connected cities and no other cities outside of the group.
 * You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
 * Return the total number of provinces.
 * 
 * Example 1:
 * Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
 * Output: 2
 * 
 * Example 2:
 * Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
 * Output: 3
 * 
 * Note:
 * 1 <= n <= 200
 * n == isConnected.length
 * n == isConnected[i].length
 * isConnected[i][j] is 1 or 0.
 * isConnected[i][i] == 1
 * isConnected[i][j] == isConnected[j][i]
 * 
 */
#include <vector>
#include <functional>
#include <queue>
using namespace std;

class Solution1 {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        
        function<void(int)> dfs = [&](int i) {
            visited[i] = true;
            for (int j = 0; j < n; ++j) {
                if (isConnected[i][j] && !visited[j]) {
                    dfs(j);
                }
            }
        };
        
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i);
                provinces++;
            }
        }
        return provinces;
    }
};

class Solution2 {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        queue<int> q;
        
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                q.push(i);
                while (!q.empty()) {
                    int curr = q.front(); q.pop();
                    visited[curr] = true;
                    for (int j = 0; j < n; ++j) {
                        if (isConnected[curr][j] && !visited[j]) {
                            q.push(j);
                        }
                    }
                }
                provinces++;
            }
        }
        return provinces;
    }
};

class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else { parent[rootY] = rootX; rank[rootX]++; }
        }
    }
};

class Solution3 {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j]) uf.unite(i, j);
            }
        }
        int provinces = 0;
        for (int i = 0; i < n; ++i) {
            if (uf.find(i) == i) provinces++;
        }
        return provinces;
    }
};