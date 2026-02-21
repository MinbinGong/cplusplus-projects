/*
 * Most Frequent Subtree Sum
 *
 * Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with
 * the highest frequency in any order.
 *
 * The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node
 * (including the node itself).
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 104].
 * -105 <= Node.val <= 105
 *
 */
#include <vector>
#include <unordered_map>
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

class Solution {
 public:
  vector<int> findFrequentTreeSum(TreeNode* root) {
    unordered_map<int, int> freq;
    int maxFreq = 0;
    dfs(root, freq, maxFreq);

    vector<int> result;
    for (auto& [sum, cnt] : freq) {
      if (cnt == maxFreq) {
        result.push_back(sum);
      }
    }
    return result;
  }

 private:
  int dfs(TreeNode* node, unordered_map<int, int>& freq, int& maxFreq) {
    if (!node) return 0;
    int leftSum = dfs(node->left, freq, maxFreq);
    int rightSum = dfs(node->right, freq, maxFreq);
    int sum = leftSum + rightSum + node->val;
    freq[sum]++;
    maxFreq = max(maxFreq, freq[sum]);
    return sum;
  }
};