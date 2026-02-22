/*
 * Smallest Range Covering Elements from K Lists
 * 
 * You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
 * 
 * We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
 * 
 * Example 1:
 * Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
 * Output: [20,24]
 * Explanation: 
 * List 1: [4, 10, 15, 24, 26], 24 is in range [20,24].
 * List 2: [0, 9, 12, 20], 20 is in range [20,24].
 * List 3: [5, 18, 22, 30], 22 is in range [20,24].
 * 
 * Example 2:
 * Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
 * Output: [1,1]
 * 
 * Constraints:
 * nums.length == k
 * 1 <= k <= 3500
 * 1 <= nums[i].length <= 50
 * -105 <= nums[i][j] <= 105
 * nums[i] is sorted in non-decreasing order.
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // 最小堆，存储 (元素值, 所在列表索引, 在列表中的位置)
        struct Element {
            int val, list, idx;
            bool operator>(const Element& other) const {
                return val > other.val;
            }
        };
        priority_queue<Element, vector<Element>, greater<Element>> pq;
        
        int maxVal = INT_MIN;
        // 初始化：每个列表的第一个元素入堆，并记录当前最大值
        for (int i = 0; i < nums.size(); ++i) {
            if (!nums[i].empty()) {
                pq.push({nums[i][0], i, 0});
                maxVal = max(maxVal, nums[i][0]);
            }
        }
        
        int bestStart = -1, bestEnd = -1;
        int bestRange = INT_MAX;
        
        while (true) {
            // 取出当前最小元素
            auto cur = pq.top();
            pq.pop();
            int curMin = cur.val;
            int curRange = maxVal - curMin;
            
            // 更新最优区间
            if (curRange < bestRange) {
                bestRange = curRange;
                bestStart = curMin;
                bestEnd = maxVal;
            }
            
            // 如果当前列表还有下一个元素，则将其入堆，并更新最大值
            if (cur.idx + 1 < nums[cur.list].size()) {
                int nextVal = nums[cur.list][cur.idx + 1];
                pq.push({nextVal, cur.list, cur.idx + 1});
                maxVal = max(maxVal, nextVal);
            } else {
                // 某个列表已耗尽，无法再构成覆盖所有列表的区间，结束循环
                break;
            }
        }
        
        return {bestStart, bestEnd};
    }
};