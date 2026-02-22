/*
 * Path Sum IV
 *
 * If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.
 *
 * For each integer in this list:
 *
 * The hundreds digit represents the depth D of this node, 1 <= D <= 4.
 * The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8. The position is the
 * same as that in a full binary tree. The units digit represents the value V of this node, 0 <= V <= 9.
 *
 * Given a list of ascending three-digits integers representing a binary with the depth smaller than 5. You need to
 * return the sum of all paths from the root towards the leaves.
 *
 * Example 1:
 *
 * Input: [113, 215, 221]
 * Output: 12
 * Explanation:
 * The tree that the list represents is:
 *     3
 *    / \
 *   5   1
 *
 * Example 2:
 *
 * Input: [113, 221]
 * Output: 4
 * Explanation:
 * The tree that the list represents is:
 *     3
 *      \
 *       1
 *
 * Note: The n belongs to [1, 100].
 *
 */
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int pathSum(vector<int>& nums) {
    // 构建节点映射：key = depth * 10 + position, value = node value
    unordered_map<int, int> treeMap;
    for (int num : nums) {
      int depth = num / 100;           // 百位：深度
      int position = (num / 10) % 10;  // 十位：位置
      int value = num % 10;            // 个位：节点值
      treeMap[depth * 10 + position] = value;
    }

    int totalSum = 0;
    dfs(treeMap, 1, 1, 0, totalSum);  // 从根节点(1,1)开始DFS
    return totalSum;
  }

 private:
  void dfs(unordered_map<int, int>& treeMap, int depth, int pos, int currentSum, int& totalSum) {
    int key = depth * 10 + pos;
    if (treeMap.find(key) == treeMap.end()) {
      return;  // 节点不存在
    }

    // 累加当前路径和
    currentSum += treeMap[key];

    // 计算左右子节点的key
    int leftKey = (depth + 1) * 10 + (pos * 2 - 1);
    int rightKey = (depth + 1) * 10 + (pos * 2);

    // 如果是叶子节点（左右子节点都不存在），加入总和
    if (treeMap.find(leftKey) == treeMap.end() && treeMap.find(rightKey) == treeMap.end()) {
      totalSum += currentSum;
      return;
    }

    // 递归遍历存在的子节点
    dfs(treeMap, depth + 1, pos * 2 - 1, currentSum, totalSum);
    dfs(treeMap, depth + 1, pos * 2, currentSum, totalSum);
  }
};