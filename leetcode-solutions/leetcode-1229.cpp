/**
 * 1229. Meeting Scheduler
 *
 * Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, return the earliest time slot that works for both of them and is of duration duration.
 *
 * If there is no common time slot that satisfies the requirements, return an empty array.
 *
 * The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.
 *
 * It is guaranteed that no two availability slots of the same person intersect with each other. That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.
 *
 *
 *
 * Example 1:
 *
 * Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
 * Output: [60,68]
 *
 * Example 2:
 *
 * Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
 * Output: []
 *
 *
 * Constraints:
 *
 * 1 <= slots1.length, slots2.length <= 10^4
 * slots1[i].length, slots2[i].length == 2
 * slots1[i][0] < slots1[i][1]
 * slots2[i][0] < slots2[i][1]
 * 0 <= slots1[i][j], slots2[i][j] <= 10^9
 * 1 <= duration <= 10^6
 *
 */
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution1 {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        // 按开始时间排序两个时间区间列表
        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());
        
        int i = 0, j = 0;
        int m = slots1.size(), n = slots2.size();
        
        while (i < m && j < n) {
            // 计算当前两个时间区间的交集
            int start = max(slots1[i][0], slots2[j][0]);
            int end = min(slots1[i][1], slots2[j][1]);
            
            // 如果交集长度大于等于会议持续时间
            if (end - start >= duration) {
                return {start, start + duration};
            }
            
            // 移动结束时间较早的区间指针
            if (slots1[i][1] < slots2[j][1]) {
                i++;
            } else {
                j++;
            }
        }
        
        // 没有找到合适的时间段
        return {};
    }
};

// 方法2：使用优先队列（最小堆）合并区间
class Solution2 {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        // 使用最小堆按开始时间排序所有区间
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0]; // 最小堆，开始时间小的在前
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        
        // 将所有区间加入优先队列
        for (const auto& slot : slots1) {
            if (slot[1] - slot[0] >= duration) {
                pq.push(slot);
            }
        }
        for (const auto& slot : slots2) {
            if (slot[1] - slot[0] >= duration) {
                pq.push(slot);
            }
        }
        
        // 合并区间并查找合适的会议时间
        while (pq.size() > 1) {
            auto first = pq.top(); pq.pop();
            auto second = pq.top();
            
            int start = max(first[0], second[0]);
            int end = min(first[1], second[1]);
            
            if (end - start >= duration) {
                return {start, start + duration};
            }
            
            // 保留结束时间较晚的区间
            if (first[1] < second[1]) {
                pq.push(second);
            } else {
                pq.push(first);
            }
        }
        
        return {};
    }
};

// 方法3：先合并再查找（更直观但效率稍低）
class Solution3 {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        // 合并两个列表
        vector<vector<int>> allSlots;
        for (const auto& slot : slots1) {
            if (slot[1] - slot[0] >= duration) {
                allSlots.push_back(slot);
            }
        }
        for (const auto& slot : slots2) {
            if (slot[1] - slot[0] >= duration) {
                allSlots.push_back(slot);
            }
        }
        
        // 按开始时间排序
        sort(allSlots.begin(), allSlots.end());
        
        // 查找连续两个区间的交集
        for (int i = 0; i < (int)allSlots.size() - 1; ++i) {
            int start = max(allSlots[i][0], allSlots[i+1][0]);
            int end = min(allSlots[i][1], allSlots[i+1][1]);
            
            if (end - start >= duration) {
                return {start, start + duration};
            }
        }
        
        return {};
    }
};

// 测试用例示例：
// 输入: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
// 输出: [60,68]
// 
// 输入: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
// 输出: []