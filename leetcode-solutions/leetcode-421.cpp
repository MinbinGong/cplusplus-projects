/*
 * Maximum XOR of Two Numbers in an Array
 *
 * Given a non-empty array of numbers, a0, a1, a2, ... , an-1, where 0 ≤ ai < 231.
 * Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.
 * Could you do this in O(n) runtime?
 * 
 * Example:
 * Input: [3, 10, 5, 25, 2, 8]
 * Output: 28
 * Explanation: The maximum result is 5 ^ 25 = 28.
 * 
 * Constraints:
 * 1 <= nums.length <= 2 * 104
 * 0 <= nums[i] <= 231 - 1
 */
#include <vector>
using namespace std;

struct TrieNode {
  vector<TrieNode *> child;
  bool last;
  TrieNode() : child(2, NULL), last(false){};
};

void insert(TrieNode *root, int val) {
  TrieNode *cur = root;
  for (int i = 31; i >= 0; i--) {
    int v = (val >> i) & 1;
    if (!cur->child[v]) cur->child[v] = new TrieNode();
    cur = cur->child[v];
  }
  cur->last = true;
}

int search(TrieNode *root, int val) {
  TrieNode *cur = root;
  int res = 0;
  for (int i = 31; i >= 0; i--) {
    int v = (val >> i) & 1;
    if (cur->child[1 - v]) {
      res |= ((1 - v) << i);
      cur = cur->child[1 - v];
    } else {
      res |= (v << i);
      cur = cur->child[v];
    }
  }
  return res;
}

int findMaximumXOR(vector<int> &nums) {
  TrieNode *root = new TrieNode();
  int mx = 0;
  for (auto num : nums) insert(root, num);

  for (auto num : nums) {
    mx = max(num ^ search(root, num), mx);
  }
  return mx;
}