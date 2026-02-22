/*
 * Construct Binary Tree from String
 *
 * You need to construct a binary tree from a string consisting of parenthesis and integers.
 *
 * The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis.
 * The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same
 * structure.
 *
 * You always start to construct the left child node of the parent first if it exists.
 *
 * Example:
 * Input: "4(2(3)(1))(6(5))"
 * Output: return the tree root node representing the following tree:
 *
 *        4
 *      /   \
 *     2     6
 *    / \   /
 *   3   1 5
 *
 * Note:
 * 1. There will only be '(', ')', '-' and '0' ~ '9' in the input string.
 * 2. An empty tree is represented by "" instead of "()".
 *
 */
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution1 {
 public:
  TreeNode* str2tree(string s) {
    int idx = 0;
    return dfs(s, idx);
  }

 private:
  TreeNode* dfs(const string& s, int& idx) {
    if (idx >= s.size()) return nullptr;

    // 1. 解析节点值 (可能为负数)
    int sign = 1;
    if (s[idx] == '-') {
      sign = -1;
      idx++;
    }
    int num = 0;
    while (idx < s.size() && isdigit(s[idx])) {
      num = num * 10 + (s[idx] - '0');
      idx++;
    }
    TreeNode* node = new TreeNode(sign * num);

    // 2. 构建左子树 (如果存在 '(')
    if (idx < s.size() && s[idx] == '(') {
      idx++;  // 跳过 '('
      node->left = dfs(s, idx);
      idx++;  // 跳过 ')'
    }

    // 3. 构建右子树 (如果存在 '(')
    if (idx < s.size() && s[idx] == '(') {
      idx++;  // 跳过 '('
      node->right = dfs(s, idx);
      idx++;  // 跳过 ')'
    }

    return node;
  }
};

class Solution2 {
public:
    TreeNode* str2tree(string s) {
        if (s.empty()) return nullptr;

        stack<TreeNode*> stk;
        for (int i = 0; i < s.size();) {
            if (s[i] == '-' || isdigit(s[i])) {
                // 1. 解析数字
                int sign = 1;
                if (s[i] == '-') {
                    sign = -1;
                    i++;
                }
                int j = i;
                while (j < s.size() && isdigit(s[j])) j++;
                int val = sign * stoi(s.substr(i, j - i));
                TreeNode* node = new TreeNode(val);
                i = j; // 移动 i 到数字后一位

                // 2. 将新节点挂载到父节点上
                if (!stk.empty()) {
                    TreeNode* parent = stk.top();
                    if (!parent->left) {
                        parent->left = node;
                    } else {
                        parent->right = node;
                    }
                }
                stk.push(node);
            } else if (s[i] == ')') {
                // 3. 子树结束，弹出节点
                stk.pop();
                i++;
            } else { // s[i] == '('
                i++; // 直接跳过
            }
        }
        // 栈底元素即为根节点
        TreeNode* root = nullptr;
        while (!stk.empty()) {
            root = stk.top();
            stk.pop();
        }
        return root;
    }
};