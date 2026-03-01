/**
 * 1288. Remove Covered Intervals
 * 
 * Given a list of intervals, remove all intervals that are covered by another interval in the list.
 * 
 * Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.
 * 
 * After doing so, return the number of remaining intervals.
 * 
 * Example 1:
 * Input: intervals = [[1,4],[3,6],[2,8]]
 * Output: 2
 * Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
 * 
 * Note:
 * 1 <= intervals.length <= 1000
 * 0 <= intervals[i][0] < intervals[i][1] <= 10^5
 * intervals[i] != intervals[j] for all i != j
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // 1. 排序：左端点升序，左端点相同时右端点降序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });

        int n = intervals.size();
        int ans = n;               // 初始假设所有区间都保留
        int maxRight = -1;          // 记录遍历过的最大右端点

        // 2. 遍历判断
        for (const auto& interval : intervals) {
            if (interval[1] <= maxRight) {
                // 当前区间被覆盖
                ans--;
            } else {
                // 当前区间未被覆盖，更新最大右端点
                maxRight = interval[1];
            }
        }

        return ans;
    }
};