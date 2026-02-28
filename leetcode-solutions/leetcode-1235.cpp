/*
 * 1235. Maximum Profit in Job Scheduling
 *
 * We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].
 *
 * You're given the startTime, endTime and profit arrays, you need to output the maximum profit you can take such that there are no 2 jobs in the subset with overlapping time range.
 *
 * If you choose a job that ends at time X you will be able to start another job that starts at time X.
 *
 * Example 1:
 * 
 * Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
 * Output: 120
 * Explanation: The subset chosen is the first and fourth job. 
 * Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
 * 
 * Example 2:
 * 
 * Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
 * Output: 150
 * Explanation: The subset chosen is the first, fourth and fifth job. 
 * Profit obtained 150 = 20 + 70 + 60.
 * 
 * Example 3:
 * 
 * Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
 * Output: 6
 * 
 * Note:
 * 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
 * 1 <= startTime[i] < endTime[i] <= 10^9
 * 1 <= profit[i] <= 10^4
 * 
 */
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
#include <numeric>
using namespace std;

class Solution1 {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        
        // 合并任务信息并按结束时间排序
        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        
        // 提取排序后的数组
        vector<int> ends, starts, profits;
        for (int i = 0; i < n; ++i) {
            ends.push_back(jobs[i][0]);
            starts.push_back(jobs[i][1]);
            profits.push_back(jobs[i][2]);
        }
        
        // 动态规划
        vector<int> dp(n + 1, 0);
        dp[0] = 0;  // 前0个任务的最大利润为0
        
        for (int i = 1; i <= n; ++i) {
            // 不选择当前任务
            int notTake = dp[i - 1];
            
            // 选择当前任务
            int start = starts[i - 1];
            
            // 二分查找最后一个结束时间小于等于start的任务
            int left = 0, right = i - 2;
            int index = -1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (ends[mid] <= start) {
                    index = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            
            int take = profits[i - 1] + dp[index + 1];
            
            // 取最大值
            dp[i] = max(notTake, take);
        }
        
        return dp[n];
    }
};

// 方法2：使用STL的upper_bound
class Solution2 {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        
        vector<int> ends, profits;
        for (int i = 0; i < n; ++i) {
            ends.push_back(jobs[i][0]);
            profits.push_back(jobs[i][2]);
        }
        
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            // 不选择当前任务
            dp[i] = dp[i - 1];
            
            // 选择当前任务
            int start = jobs[i - 1][1];
            
            // 使用upper_bound找到第一个大于start的结束时间
            auto it = upper_bound(ends.begin(), ends.begin() + i - 1, start);
            int index = it - ends.begin() - 1;  // 最后一个小于等于start的索引
            
            int take = jobs[i - 1][2] + dp[index + 1];
            dp[i] = max(dp[i], take);
        }
        
        return dp[n];
    }
};

// 方法3：使用map优化查找
class Solution3 {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());  // 按开始时间排序
        
        // dp[i]表示从第i个任务开始到结束能获得的最大利润
        vector<int> dp(n + 1, 0);
        
        // 从后往前动态规划
        for (int i = n - 1; i >= 0; --i) {
            // 不选择当前任务
            int notTake = dp[i + 1];
            
            // 选择当前任务
            int end = jobs[i][1];
            int prof = jobs[i][2];
            
            // 二分查找下一个可以做的任务
            vector<int> target = {end, 0, 0};
            auto it = lower_bound(jobs.begin(), jobs.end(), target, 
                [](const vector<int>& a, const vector<int>& b) {
                    return a[0] < b[0];
                });
            int nextIdx = it - jobs.begin();
            
            int take = prof + dp[nextIdx];
            
            dp[i] = max(notTake, take);
        }
        
        return dp[0];
    }
};

// 方法4：使用TreeMap（C++中用map模拟）
#include <map>
class Solution4 {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        
        map<int, int> dp;  // dp[time]表示从时间time开始能获得的最大利润
        dp[INT_MAX] = 0;  // 哨兵
        
        for (int i = n - 1; i >= 0; --i) {
            int start = jobs[i][0];
            int end = jobs[i][1];
            int prof = jobs[i][2];
            
            // 找到第一个开始时间大于等于end的任务
            auto it = dp.lower_bound(end);
            int maxProf = prof + it->second;
            
            // 如果当前开始时间的利润更大，则更新
            it = dp.lower_bound(start);
            if (it == dp.end() || maxProf > it->second) {
                dp[start] = maxProf;
                // 维护dp的单调性
                auto it2 = dp.find(start);
                if (it2 != dp.begin()) {
                    auto prev = prev(it2);
                    if (prev->second >= maxProf) {
                        dp.erase(it2);
                    } else {
                        // 删除后面利润更小的
                        while (next(it2) != dp.end() && next(it2)->second <= maxProf) {
                            dp.erase(next(it2));
                        }
                    }
                }
            }
        }
        
        return dp.begin()->second;
    }
};

// 测试用例示例：
// 输入: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
// 输出: 120
// 解释: 选择第1个和第4个任务，利润为50+70=120
//
// 输入: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
// 输出: 150
// 解释: 选择第1、4、5个任务，利润为20+70+60=150
//
// 输入: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
// 输出: 6
// 解释: 选择第2个任务，利润为6

// 复杂度分析：
// 方法1：
// - 时间复杂度：O(n log n)，其中n是任务数量，排序O(n log n)，每个任务一次二分查找O(log n)
// - 空间复杂度：O(n)，用于存储排序后的任务和dp数组
//
// 方法2（STL版本）：
// - 时间复杂度：O(n log n)
// - 空间复杂度：O(n)
//
// 方法3（从后往前DP）：
// - 时间复杂度：O(n log n)
// - 空间复杂度：O(n)
//
// 方法4（TreeMap）：
// - 时间复杂度：O(n log n)，每个插入和查找O(log n)
// - 空间复杂度：O(n)