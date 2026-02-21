/*
 * leetcode-364: Nested List Weight Sum II
 *
 * Given a nested list of integers, return the sum of all integers in the list weighted by their depth.
 * 
 * Each element is either an integer, or a list -- whose elements may also be integers or other lists.
 * 
 * Example 1:
 * Input: [[1,1],2,[1,1]]
 * Output: 8 
 * Explanation: Four 1's at depth 1, one 2 at depth 2.
 * 
 * Example 2:
 * Input: [1,[4,[6]]]
 * Output: 17 
 * Explanation: One 1 at depth 3, one 4 at depth 2, and one 6 at depth 1; 1*3 + 4*2 + 6*1 = 17.
 * 
 * Constraints:
 * The depth of the nested list is less than 50.
 * The total number of integers in the nested list is less than 10000.
 * Each integer in the nested list is in the range [-1000, 1000].
 * 
 */
class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        vector<int> levelSum;                // 记录每一层的整数和，下标0对应深度1
        dfs(nestedList, 1, levelSum);        // 一次DFS收集各层和
        
        int total = 0;
        int maxDepth = levelSum.size();       // 最大深度
        for (int i = 0; i < maxDepth; ++i) {
            total += levelSum[i] * (maxDepth - i);   // 权重 = 最大深度 - 当前深度 + 1
        }
        return total;
    }

private:
    void dfs(vector<NestedInteger>& nestedList, int depth, vector<int>& levelSum) {
        if (levelSum.size() < depth) {
            levelSum.push_back(0);            // 扩展到当前深度
        }
        for (auto& ni : nestedList) {
            if (ni.isInteger()) {
                levelSum[depth - 1] += ni.getInteger();   // 累加到对应层
            } else {
                dfs(ni.getList(), depth + 1, levelSum);   // 递归处理子列表
            }
        }
    }
};