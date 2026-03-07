/**
 * 1627. Graph Connectivity With Threshold
 * 
 * We have n cities labeled from 1 to n. Two different cities with labels x and y are directly connected by a bidirectional road if and only if x and y share a common divisor strictly greater than some threshold. More formally, cities with labels x and y have a road between them if there exists an integer z such that all of the following are true:
 * 
 * x % z == 0,
 * y % z == 0, and
 * z > threshold.
 * Given the two integers, n and threshold, and an array of queries, you must determine for each queries[i] = [ai, bi] if cities ai and bi are connected (i.e. there is some path between them).
 * 
 * Return an array answer, where answer.length == queries.length and answer[i] is true if for the ith query, there is a path between ai and bi, or answer[i] is false if there is no path.
 * 
 * Example 1:
 * Input: n = 6, threshold = 2, queries = [[1,4],[2,5],[3,6]]
 * Output: [false,false,true]
 * Explanation: The divisors for each number:
 * 1: 1
 * 2: 1, 2
 * 3: 1, 3
 * 4: 1, 2, 4
 * 5: 1, 5
 * 6: 1, 2, 3, 6
 * Using the underlined divisors above the threshold, only cities 3 and 6 share a common divisor, so they are the
 * only ones directly connected. The result of each query:
 * [1,4] 1 is not connected to 4
 * [2,5] 2 is not connected to 5
 * [3,6] 3 is connected to 6 through path 3--6
 * 
 * Example 2:
 * Input: n = 6, threshold = 0, queries = [[4,5],[3,4],[3,2],[2,6],[1,3]]
 * Output: [true,true,true,true,true]
 * Explanation: The divisors for each number are the same as the previous example. However, since the threshold is 0, any divisor can be used.
 * 
 * Constraints:
 * 2 <= n <= 104
 * 0 <= threshold <= n
 * 1 <= queries.length <= 105
 * queries[i].length == 2
 * 1 <= ai, bi <= cities
 * ai != bi
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
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        UnionFind uf(n + 1);
        
        // 连接所有具有大于threshold的公约数的节点
        for (int d = threshold + 1; d <= n; ++d) {
            for (int multiple = d * 2; multiple <= n; multiple += d) {
                uf.unite(d, multiple);
            }
        }
        
        vector<bool> result;
        for (const auto& q : queries) {
            int x = q[0], y = q[1];
            result.push_back(uf.connected(x, y));
        }
        return result;
    }
};