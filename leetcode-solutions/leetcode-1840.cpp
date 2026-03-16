/**
 * 1840. Maximum Building Height
 * https://leetcode.com/problems/maximum-building-height/
 * 
 * You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.
 * 
 * However, there are city restrictions on the heights of the new buildings:
 * 
 * The height of each building must be a non-negative integer.
 * The height of the first building must be 0.
 * The height difference between any two adjacent buildings cannot exceed 1.
 * Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.
 * 
 * It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.
 * 
 * Return the maximum possible height of the tallest building.
 * 
 * Example 1:
 * Input: n = 5, restrictions = [[2,1],[4,1]]
 * Output: 2
 * Explanation: The green area in the image indicates the maximum allowed height for each building.
 * We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
 * 
 * Example 2:
 * Input: n = 6, restrictions = []
 * Output: 5
 * Explanation: The green area in the image indicates the maximum allowed height for each building.
 * We can build the buildings with heights [0,1,2,3,4,5], and the tallest building has a height of 5. Notice that the restrictions are empty, so all buildings can have the maximum height.
 * 
 * Example 3:
 * Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
 * Output: 5
 * Explanation: The green area in the image indicates the maximum allowed height for each building.
 * We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the tallest building has a height of 5.
 * 
 * Constraints:
 * 2 <= n <= 109
 * 0 <= restrictions.length <= min(n - 1, 105)
 * 2 <= idi <= n
 * idi is unique.
 * 0 <= maxHeighti <= 109
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // 1. 添加并整理所有限制点
        vector<pair<int, int>> points;
        // 建筑1的高度必须为0
        points.emplace_back(1, 0);
        for (auto& r : restrictions) {
            // 初步剪枝：任何建筑的高度都不可能超过其编号减1（因为从1开始，每次最多+1）
            points.emplace_back(r[0], min(r[1], r[0] - 1));
        }
        // 为最后一个建筑添加虚拟限制（如果不存在）
        if (points.back().first != n) {
            points.emplace_back(n, n - 1);
        }

        // 2. 按建筑编号排序
        sort(points.begin(), points.end());

        int m = points.size();

        // 3. 正向传递：从左向右，让后面的点受前面点约束
        for (int i = 1; i < m; ++i) {
            int id1 = points[i-1].first, h1 = points[i-1].second;
            int id2 = points[i].first, h2 = points[i].second;
            points[i].second = min(h2, h1 + (id2 - id1));
        }

        // 4. 反向传递：从右向左，让前面的点受后面点约束
        for (int i = m - 2; i >= 0; --i) {
            int id1 = points[i].first, h1 = points[i].second;
            int id2 = points[i+1].first, h2 = points[i+1].second;
            points[i].second = min(h1, h2 + (id2 - id1));
        }

        // 5. 计算每个区间内的可能的最大高度，并取最大值
        int ans = 0;
        for (int i = 1; i < m; ++i) {
            int id1 = points[i-1].first, h1 = points[i-1].second;
            int id2 = points[i].first, h2 = points[i].second;
            // 区间内最高点公式
            int maxH = (h1 + h2 + (id2 - id1)) / 2;
            ans = max(ans, maxH);
        }

        return ans;
    }
};
