/**
 * 1632. Rank Transform of a Matrix
 * 
 * Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].
 * 
 * The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:
 * 
 * If an element is the smallest in its row and column, then its rank is 1.
 * If two elements p and q are in the same row or column, then:
 * If p < q then rank(p) < rank(q)
 * If p == q then rank(p) == rank(q)
 * If p > q then rank(p) > rank(q)
 * The rank should be as small as possible.
 * It is guaranteed that answer is unique under the given rules.
 * 
 * Example 1:
 * Input: matrix = [[1,2],[3,4]]
 * Output: [[1,2],[2,3]]
 * Explanation:
 * The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
 * The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][1] is the smallest integer in its row.
 * The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[1][0] is the smallest integer in its column.
 * The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and matrix[1][1] is the largest integer in its row and column.
 * 
 * Example 2:
 * Input: matrix = [[7,7],[7,7]]
 * Output: [[1,1],[1,1]]
 * 
 * Example 3:
 * Input: matrix = [[20,-21,14],[-19,4,19],[22,-47,24],[-19,4,19]]
 * Output: [[4,2,3],[1,3,4],[5,1,6],[1,3,4]]
 * 
 * Example 4:
 * Input: matrix = [[7,3,6],[1,4,5],[9,8,2]]
 * Output: [[5,1,4],[1,2,3],[6,3,1]]
 * 
 * Constraints:
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 500
 * -109 <= matrix[row][col] <= 109
 * 
 */
#include <vector>
using namespace std;

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
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 按值分组存储位置
        map<int, vector<pair<int, int>>> valPos;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                valPos[matrix[i][j]].push_back({i, j});
            }
        }
        
        vector<int> rowRank(m, 0), colRank(n, 0);
        vector<vector<int>> result(m, vector<int>(n, 0));
        
        // 按值从小到大处理
        for (auto& [val, positions] : valPos) {
            // 并查集，行编号 0~m-1，列编号 m~m+n-1
            UnionFind uf(m + n);
            // 将同一行或同一列的位置合并
            for (auto& [r, c] : positions) {
                uf.unite(r, m + c);
            }
            
            // 按连通分量分组
            unordered_map<int, vector<pair<int, int>>> compPos;
            for (auto& [r, c] : positions) {
                int root = uf.find(r);
                compPos[root].push_back({r, c});
            }
            
            // 处理每个连通分量
            for (auto& [root, posList] : compPos) {
                // 计算当前连通分量中的最大 rank
                int maxRank = 0;
                for (auto& [r, c] : posList) {
                    maxRank = max(maxRank, max(rowRank[r], colRank[c]));
                }
                int newRank = maxRank + 1;
                // 更新 result 并更新 rowRank 和 colRank
                for (auto& [r, c] : posList) {
                    result[r][c] = newRank;
                    rowRank[r] = newRank;
                    colRank[c] = newRank;
                }
            }
        }
        return result;
    }
};