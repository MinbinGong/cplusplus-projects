/*
 * Meeting Rooms II
 * 
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.
 * 
 * Constraints:
 * 1. 1 <= intervals.length <= 104
 * 2. 0 <= starti < endi <= 106
 */
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

class Solution1 {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // 1. 按会议开始时间排序
        sort(intervals.begin(), intervals.end());

        // 最小堆，存储会议的结束时间
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // 2. 遍历每个会议
        for (const auto& interval : intervals) {
            // 如果当前最早结束的会议在本次会议开始前就结束了，就可以复用这个会议室
            if (!minHeap.empty() && minHeap.top() <= interval[0]) {
                minHeap.pop(); // 把原来的会议弹出
            }
            // 将当前会议的结束时间加入堆中
            minHeap.push(interval[1]);
        }

        // 堆的大小即为所需的最少会议室数
        return minHeap.size();
    }
};

class Solution2 {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> starts, ends;
        for (const auto& interval : intervals) {
            starts.push_back(interval[0]);
            ends.push_back(interval[1]);
        }

        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        int rooms = 0, maxRooms = 0;
        int s_ptr = 0, e_ptr = 0;

        while (s_ptr < intervals.size()) {
            if (starts[s_ptr] < ends[e_ptr]) {
                // 会议开始，且无空闲会议室，房间数增加
                rooms++;
                s_ptr++;
            } else {
                // 会议结束，空出会议室
                rooms--;
                e_ptr++;
            }
            maxRooms = max(maxRooms, rooms);
        }
        return maxRooms;
    }
};

class Solution3 {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> timeline; // map 会自动按照 key (时间) 排序
        for (const auto& interval : intervals) {
            timeline[interval[0]]++;  // 开始时间，房间需求 +1
            timeline[interval[1]]--;  // 结束时间，房间需求 -1
        }

        int rooms = 0, maxRooms = 0;
        for (const auto& [time, change] : timeline) {
            rooms += change;
            maxRooms = max(maxRooms, rooms);
        }
        return maxRooms;
    }
};