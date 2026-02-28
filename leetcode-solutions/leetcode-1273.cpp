/**
 * 1273. Delete Tree Nodes
 * 
 * A tree rooted at node 0 is given as follows:
 * 
 * The number of nodes is nodes;
 * The value of the i-th node is value[i];
 * The parent of the i-th node is parent[i].
 * Remove every subtree whose sum of values of nodes is zero.
 * 
 * After doing so, return the number of nodes remaining in the tree.
 * 
 * Example 1:
 * Input: nodes = 7, parent = [-1,0,0,1,2,2,2], value = [1,-2,4,0,-2,-1,-1]
 * Output: 2
 * 
 * Note:
 * 1 <= nodes <= 10^4
 * -10^5 <= value[i] <= 10^5
 * parent.length == nodes
 * parent[0] == -1 which indicates that 0 is the root.
 * 
 */
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    int deleteTreeNodes(int n, vector<int>& parent, vector<int>& value) {
        // 构建孩子列表
        vector<vector<int>> children(n);
        int root = -1;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == -1) {
                root = i;
            } else {
                children[parent[i]].push_back(i);
            }
        }

        // 后序遍历，返回 {子树和, 剩余节点数}
        function<pair<int,int>(int)> dfs = [&](int u) -> pair<int,int> {
            int sum = value[u];
            int cnt = 1;  // 当前节点先计为1（可能被删除）
            for (int v : children[u]) {
                auto [childSum, childCnt] = dfs(v);
                sum += childSum;
                cnt += childCnt;
            }
            // 如果子树和为0，则整个子树删除
            if (sum == 0) {
                return {0, 0};
            }
            return {sum, cnt};
        };

        return dfs(root).second;
    }
};