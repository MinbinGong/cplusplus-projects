/**
 * 1483. Kth Ancestor of a Tree Node
 * 
 * You are given a tree with n nodes numbered from 0 to n-1 in the form of a parent array where parent[i] is the parent of node i. The root of the tree is node 0.
 * 
 * Implement the function getKthAncestor(int node, int k) to return the k-th ancestor of the given node. If there is no such ancestor, return -1.
 * 
 * The k-th ancestor of a tree node is the k-th node in the path from that node to the root.
 * 
 * Example:
 * 
 * Input:
 * ["TreeAncestor","getKthAncestor","getKthAncestor","getKthAncestor"]
 * [[7,[-1,0,0,1,1,2,2]],[3,1],[5,2],[6,3]]
 * 
 * Output:
 * [null,1,0,-1]
 * 
 * Explanation:
 * TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);
 * treeAncestor.getKthAncestor(3, 1);  // returns 1 which is the parent of 3
 * treeAncestor.getKthAncestor(5, 2);  // returns 0 which is the grandparent of 5
 * treeAncestor.getKthAncestor(6, 3);  // returns -1 because there is no such ancestor
 * 
 * Constraints:
 * 1 <= k <= n <= 5*10^4
 * parent[0] == -1 indicating that 0 is the root node.
 * 0 <= parent[i] < n for all 0 < i < n
 * 0 <= node < n
 * There will be at most 5*10^4 queries.
 * 
 */
#include <vector>
using namespace std;

class TreeAncestor {
private:
    vector<vector<int>> dp; // dp[node][i] 表示 node 的第 2^i 个祖先
    int maxPow;             // 需要的最大幂次，满足 2^maxPow >= n
public:
    TreeAncestor(int n, vector<int>& parent) {
        // 计算需要的最大幂次（log2(n) 向上取整）
        maxPow = 0;
        while ((1 << maxPow) <= n) ++maxPow;
        
        // 初始化 dp 表，大小为 n × maxPow，全部填充 -1
        dp.assign(n, vector<int>(maxPow, -1));
        
        // 第 2^0 = 1 个祖先就是直接父节点
        for (int i = 0; i < n; ++i) {
            dp[i][0] = parent[i];
        }
        
        // 动态规划填充 dp 表
        for (int j = 1; j < maxPow; ++j) {
            for (int i = 0; i < n; ++i) {
                if (dp[i][j - 1] != -1) {
                    dp[i][j] = dp[ dp[i][j - 1] ][j - 1];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        // 将 k 拆解为二进制，依次向上跳
        for (int j = 0; j < maxPow; ++j) {
            if (k & (1 << j)) {          // 如果 k 的第 j 位是 1
                node = dp[node][j];
                if (node == -1) return -1;
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */