/**
 * 1214. Two Sum BSTs
 *
 * Given the roots of two binary search trees, root1 and root2, return true if and only if there is a node in the first tree and a node in the second tree whose values sum up to a given integer target.
 *
 *
 *
 * Example 1:
 *
 * Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
 * Output: true
 * Explanation: 2 and 3 sum up to 5.
 *
 * Example 2:
 *
 * Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
 * Output: false
 *
 *
 * Constraints:
 *
 * The number of nodes in each tree is in the range [1, 5000].
 * -10^9 <= Node.val, target <= 10^9
 *
 */
#include <vector>
#include <stack>
#include <unordered_set>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution1 {
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        // 方法1：使用哈希集合，时间复杂度 O(n+m)，空间复杂度 O(n)
        std::unordered_set<int> values;
        
        // 中序遍历第一棵树，将所有值存入哈希集合
        std::stack<TreeNode*> st;
        TreeNode* curr = root1;
        while (curr != nullptr || !st.empty()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            values.insert(curr->val);
            curr = curr->right;
        }
        
        // 中序遍历第二棵树，检查是否有值使得两数之和等于target
        curr = root2;
        while (curr != nullptr || !st.empty()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            if (values.count(target - curr->val) > 0) {
                return true;
            }
            curr = curr->right;
        }
        
        return false;
    }
};

// 方法2：双指针遍历两个有序数组
class Solution2 {
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        std::vector<int> arr1, arr2;
        inorder(root1, arr1);
        inorder(root2, arr2);
        
        int i = 0, j = arr2.size() - 1;
        while (i < arr1.size() && j >= 0) {
            int sum = arr1[i] + arr2[j];
            if (sum == target) {
                return true;
            } else if (sum < target) {
                i++;
            } else {
                j--;
            }
        }
        return false;
    }
    
private:
    void inorder(TreeNode* root, std::vector<int>& arr) {
        if (root == nullptr) return;
        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);
    }
};
