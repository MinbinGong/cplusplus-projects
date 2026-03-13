/**
 * 1782. Count Pairs Of Nodes
 * 
 * You are given an undirected graph represented by an integer n, which is the number of nodes, and edges, where edges[i] = [ui, vi] which indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.
 * 
 * The answer to the jth query is the number of pairs of nodes (a, b) that satisfy the following conditions:
 * 
 * a < b
 * cnt is strictly greater than queries[j], where cnt is the number of edges incident to a or b.
 * 
 * Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.
 * 
 * Note that there can be repeated edges.
 * 
 * Example 1:
 * 
 * Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
 * Output: [6,5]
 * Explanation: The pairs of nodes that satisfy the conditions for each query are
 * - (1,2) because there are 2 edges incident to 1.
 * - (1,3) because there are 2 edges incident to 1.
 * - (1,4) because there are 3 edges incident to 1, including (1,2) and (1,3).
 * - (2,3) because there are 2 edges incident to 2.
 * - (2,4) because there are 3 edges incident to 2, including (2,1) and (2,3).
 * - (3,4) because there are 2 edges incident to 3.
 * 
 * Example 2:
 * 
 * Input: n = 5, edges = [[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]], queries = [1,2,3,4,5]
 * Output: [10,10,9,8,6]
 * Explanation: The pairs of nodes that satisfy the conditions for each query are
 * - (1,2) because there are 2 edges incident to 1.
 * - (1,3) because there are 2 edges incident to 1.
 * - (1,4) because there are 3 edges incident to 1, including (1,2) and (1,3).
 * - (2,3) because there are 2 edges incident to 2.
 * - (2,4) because there are 3 edges incident to 2, including (2,1) and (2,3).
 * - (3,4) because there are 2 edges incident to 3.
 * 
 * Constraints:
 * 
 * 2 <= n <= 2 * 104
 * 1 <= edges.length <= 105
 * 1 <= ui, vi <= n
 * ui != vi
 * 1 <= queries.length <= 20
 * 0 <= queries[j] < edges.length
 * 
 */
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        // 计算每个节点的度数
        vector<int> deg(n, 0);
        for (auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            ++deg[u];
            ++deg[v];
        }

        // 排序度数，用于双指针统计
        vector<int> sortedDeg = deg;
        sort(sortedDeg.begin(), sortedDeg.end());

        // 统计每条边的度数之和出现的次数（用于后续减去因公共边而无效的点对）
        int maxSum = 2 * n;                 // 度数之和的最大可能值
        vector<int> sumCount(maxSum + 1, 0);
        for (auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            int s = deg[u] + deg[v];
            if (s <= maxSum) ++sumCount[s];
        }

        vector<int> ans;
        for (int q : queries) {
            // 双指针：统计所有满足 deg[a] + deg[b] > q 的点对（a < b）
            int total = 0;
            int l = 0, r = n - 1;
            while (l < r) {
                if (sortedDeg[l] + sortedDeg[r] > q) {
                    total += (r - l);
                    --r;
                } else {
                    ++l;
                }
            }

            // 减去那些因为有一条公共边而导致实际和不大于 q 的点对
            // 这些点对恰好满足 deg[u]+deg[v] == q+1
            if (q + 1 <= maxSum) {
                total -= sumCount[q + 1];
            }
            ans.push_back(total);
        }
        return ans;
    }
};