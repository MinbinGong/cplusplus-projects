/**
 * 1743. Restore the Array From Adjacent Pairs
 * 
 * There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
 * You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
 * It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
 * Return the original array nums. If there are multiple solutions, return any of them.
 * 
 * Example 1:
 * Input: adjacentPairs = [[2,1],[3,4],[3,2]]
 * Output: [1,2,3,4]
 * Explanation: This array has all its adjacent pairs in adjacentPairs.
 * Notice that adjacentPairs[i] may not be in left-to-right order.
 * 
 * Example 2:
 * Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
 * Output: [-2,4,1,-3]
 * Explanation: There can be negative numbers.
 * Another solution is [-3,1,4,-2], which would also be accepted.
 * 
 * Example 3:
 * Input: adjacentPairs = [[100000,-100000]]
 * Output: [100000,-100000]
 * 
 * Constraints:
 * nums.length == n
 * adjacentPairs.length == n - 1
 * adjacentPairs[i].length == 2
 * 2 <= n <= 105
 * -105 <= nums[i], ui, vi <= 105
 * There exists some nums that has adjacentPairs as its pairs.
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> graph;
        // 构建邻接表
        for (auto& pair : adjacentPairs) {
            graph[pair[0]].push_back(pair[1]);
            graph[pair[1]].push_back(pair[0]);
        }

        // 找到起点（度为1的节点）
        int start = 0;
        for (auto& [key, neighbors] : graph) {
            if (neighbors.size() == 1) {
                start = key;
                break;
            }
        }

        vector<int> res;
        res.push_back(start);
        int prev = start;
        int cur = graph[start][0]; // 第一个邻居

        // 依次遍历直到所有节点都被加入
        while (res.size() < graph.size()) {
            res.push_back(cur);
            for (int next : graph[cur]) {
                if (next != prev) {
                    prev = cur;
                    cur = next;
                    break;
                }
            }
        }
        return res;
    }
};