/*
 * 1182. Shortest Distance to Target Color
 * 
 * You are given an array colors, in which there are three colors: 1, 2 and 3.
 * 
 * You are also given some queries. Each query consists of two integers i and c, return the shortest distance between the given index i and the target color c. If there is no solution return -1.
 * 
 * Example 1:
 * Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
 * Output: [3,0,3]
 * Explantion: 
 * The nearest 3 from index 1 is at index 4 (3 steps away).
 * The nearest 2 from index 2 is at index 2 itself (0 steps away).
 * The nearest 1 from index 6 is at index 3 (3 steps away).
 * 
 * Example 2:
 * Input: colors = [1,2], queries = [[0,3]]
 * Output: [-1]
 * Explantion: There is no 3 in the array.
 * 
 * Note:
 * 1 <= colors.length <= 5*10^4
 * 1 <= colors[i] <= 3
 * 1 <= queries.length <= 5*10^4
 * queries[i].length == 2
 * 0 <= queries[i][0] < colors.length
 * 1 <= queries[i][1] <= 3
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        // 1. 预处理：建立 颜色 -> 下标列表 的映射
        unordered_map<int, vector<int>> colorToIndices;
        for (int i = 0; i < colors.size(); ++i) {
            colorToIndices[colors[i]].push_back(i);
        }

        vector<int> ans;
        // 2. 处理每个查询
        for (const auto& query : queries) {
            int index = query[0];
            int color = query[1];

            // 如果该颜色从未出现过
            if (colorToIndices.find(color) == colorToIndices.end()) {
                ans.push_back(-1);
                continue;
            }

            const vector<int>& indices = colorToIndices[color];

            // 使用二分查找找到第一个 >= index 的位置
            auto it = lower_bound(indices.begin(), indices.end(), index);

            // 情况 1: 所有目标颜色都在右侧
            if (it == indices.begin()) {
                ans.push_back(*it - index);
            }
            // 情况 2: 所有目标颜色都在左侧
            else if (it == indices.end()) {
                ans.push_back(index - *(it - 1));
            }
            // 情况 3: 目标颜色分布在两侧，取距离更小的那个
            else {
                int rightDist = *it - index;
                int leftDist = index - *(it - 1);
                ans.push_back(min(leftDist, rightDist));
            }
        }
        return ans;
    }
};