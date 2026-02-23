/*
 * 759. Employee Free Time
 *
 * We are given a list schedule of employees, which represents the working time for each employee.
 * 
 * Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.
 * 
 * Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.
 * 
 * Example 1:
 * 
 * Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
 * Output: [[3,4]]
 * Explanation:
 * There are a total of three employees, and all common
 * free time intervals would be [-inf, 1], [3, 4], [10, inf].
 * We discard any intervals that contain inf as they aren't finite.
 * 
 * Example 2:
 * 
 * Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
 * Output: [[5,6],[7,9]]
 * Explanation:
 * Although there are a lot of finite time intervals, we only care about the common, positive-length free time intervals.
 * 
 * Note:
 * 1. schedule and schedule[i] are lists with lengths in range [1, 50].
 * 2. 0 <= schedule[i].start < schedule[i].end <= 10^8.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> employeeFreeTime(vector<vector<vector<int>>>& schedule) {
        // Flatten all intervals
        vector<vector<int>> intervals;
        for (const auto& employee : schedule) {
            for (const auto& interval : employee) {
                intervals.push_back(interval);
            }
        }

        // Sort by start time
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        // Merge overlapping or touching intervals
        vector<vector<int>> merged;
        for (const auto& iv : intervals) {
            if (merged.empty() || iv[0] > merged.back()[1]) {
                merged.push_back(iv);
            } else {
                merged.back()[1] = max(merged.back()[1], iv[1]);
            }
        }

        // Collect gaps between merged busy intervals
        vector<vector<int>> freeTime;
        for (size_t i = 1; i < merged.size(); ++i) {
            int prevEnd = merged[i - 1][1];
            int currStart = merged[i][0];
            if (prevEnd < currStart) {
                freeTime.push_back({prevEnd, currStart});
            }
        }

        return freeTime;
    }
};