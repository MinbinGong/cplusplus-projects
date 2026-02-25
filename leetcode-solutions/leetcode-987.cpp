/**
 * 987. Vertical Order Traversal of a Binary Tree
 *
 * Given a binary tree, return the vertical order traversal of its nodes values.
 *
 * For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).
 *
 * Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values of the nodes in order from top to bottom (decreasing Y coordinates).
 *
 * If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.
 *
 * Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.
 *
 * Example 1:
 *
 * Input: [3,9,20,null,null,15,7]
 * Output: [[9],[3,15],[20],[7]]
 * Explanation:
 * In the above image, the nodes are reported as [9], [3,15], [20], [7].
 * 
 * Example 2:
 *
 * Input: [1,2,3,4,5,6,7]
 * Output: [[4],[2],[1,5,6],[3],[7]]
 * Explanation:
 * The node with value 5 and the node with value 6 have the same position according to the given scheme.
 * However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.
 * 
 * Note:
 *
 * The tree will have between 1 and 1000 nodes.
 * Each node's value will be between 0 and 1000.
 */
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // map column -> list of (row, value)
        map<int, vector<pair<int, int>>> colMap;
        dfs(root, 0, 0, colMap);

        vector<vector<int>> result;
        for (auto& [col, vec] : colMap) {
            // sort by row, then by value
            sort(vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second < b.second;
            });
            // extract values
            vector<int> colVals;
            for (auto& p : vec) {
                colVals.push_back(p.second);
            }
            result.push_back(colVals);
        }
        return result;
    }

private:
    void dfs(TreeNode* node, int row, int col, map<int, vector<pair<int, int>>>& colMap) {
        if (!node) return;
        colMap[col].emplace_back(row, node->val);
        dfs(node->left, row + 1, col - 1, colMap);
        dfs(node->right, row + 1, col + 1, colMap);
    }
};