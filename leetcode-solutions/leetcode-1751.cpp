/**
 * 1751. Maximum Number of Events That Can Be Attended II
 * 
 * You are given an array of events where events[i] = [startDayi, endDayi, valuei].
 * The ith event starts at startDayi and ends at endDayi, and if you attend this
 * event, you will receive a value of valuei. You are also given an integer k which
 * represents the maximum number of events you can attend.
 * 
 * You can only attend one event at a time. If you choose to attend an event, you
 * must attend the entire event. Note that the end day is inclusive: that is, you
 * cannot attend two events where one of them starts and the other ends on the same
 * day.
 * 
 * Return the maximum sum of values that you can receive by attending events.
 * 
 * Example 1:
 * 
 * Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
 * Output: 7
 * Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
 * 
 * Example 2:
 * 
 * Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
 * Output: 10
 * Explanation: Choose event 2 for a total value of 10.
 * Notice that you cannot attend any other event as they overlap, and that you do not have to attend k events.
 * 
 * Constraints:
 * 
 * 1 <= k <= events.length
 * 1 <= k * events.length <= 106
 * 1 <= startDayi <= endDayi <= 109
 * 1 <= valuei <= 106
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        // 按结束时间排序
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // pre[i] 表示在会议 i 之前最后一个结束时间 < 会议 i 开始时间的会议下标，-1 表示不存在
        vector<int> pre(n, -1);
        for (int i = 0; i < n; ++i) {
            int l = 0, r = i - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (events[mid][1] < events[i][0]) {
                    pre[i] = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }

        // 滚动数组：dp_prev 存储选 t-1 个会议的最优值，dp_curr 存储选 t 个会议的最优值
        vector<int> dp_prev(n, 0);
        vector<int> dp_curr(n, 0);
        int ans = 0;

        for (int t = 1; t <= k; ++t) {
            for (int i = 0; i < n; ++i) {
                // 情况1：不选当前会议
                if (i > 0) dp_curr[i] = dp_curr[i - 1];
                else dp_curr[i] = 0;

                // 情况2：选当前会议
                int val = events[i][2];
                if (pre[i] != -1) {
                    val += dp_prev[pre[i]];   // 加上之前选 t-1 个会议的最优值
                }
                dp_curr[i] = max(dp_curr[i], val);
            }
            swap(dp_prev, dp_curr);        // 准备下一轮
            ans = max(ans, dp_prev[n - 1]); // 更新全局最优
        }
        return ans;
    }
};