/**
 * 1361. Validate Binary Tree Nodes
 *
 * You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
 *
 * If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
 *
 * Note that the nodes have no values and that we only use the node numbers in this problem.
 * 
 * Example 1:
 * Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
 * Output: true
 * 
 * Example 2:
 * Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
 * Output: false
 * 
 * Example 3:
 * Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
 * Output: false
 * 
 * Note:
 * The given nodes may not be connected.
 * The given nodes may not be root.
 * The given nodes may not have children.
 * The given nodes may not have more than one parent.
 * 
 */
#include <vector>
#include <queue>

class Solution {
public:
    bool validateBinaryTreeNodes(int n, std::vector<int>& leftChild, std::vector<int>& rightChild) {
        // parent[i] stores the parent of node i, or -1 if none yet
        std::vector<int> parent(n, -1);

        for (int i = 0; i < n; ++i) {
            int left = leftChild[i];
            if (left != -1) {
                // left child already has a parent? -> multiple parents
                if (parent[left] != -1) return false;
                parent[left] = i;
            }
            int right = rightChild[i];
            if (right != -1) {
                if (parent[right] != -1) return false;
                parent[right] = i;
            }
            // If left == right (same child for both), the second assignment will trigger the error.
        }

        // Find the root: node with no parent
        int root = -1;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == -1) {
                if (root != -1) return false;   // more than one root
                root = i;
            }
        }
        if (root == -1) return false;            // no root (cycle or forest)

        // BFS from root to check connectivity and detect cycles
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        q.push(root);
        visited[root] = true;
        int count = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ++count;

            int l = leftChild[u];
            if (l != -1) {
                if (visited[l]) return false;    // cycle or duplicate reachable
                visited[l] = true;
                q.push(l);
            }
            int r = rightChild[u];
            if (r != -1) {
                if (visited[r]) return false;
                visited[r] = true;
                q.push(r);
            }
        }

        return count == n;   // all nodes must be visited
    }
};