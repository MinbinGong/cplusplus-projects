/**
 * 1723. Find Minimum Time to Finish All Jobs
 * 
 * You are given an integer array jobs, where jobs[i] is the amount of time it takes to complete the ith job.
 * 
 * There are k workers that you can assign jobs to. Each job should be assigned to exactly one worker. The working time of a worker is the sum of the time it takes to complete all jobs assigned to them. Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.
 * 
 * Return the minimum possible maximum working time of any assignment.
 * 
 * Example 1:
 * Input: jobs = [3,2,3], k = 3
 * Output: 3
 * Explanation: By assigning each person one job, the maximum time is 3.
 * 
 * Example 2:
 * Input: jobs = [1,2,4,7,8], k = 2
 * Output: 11
 * Explanation: Assign the jobs the following way:
 * Worker 1: [1,2,8] (working time = 1 + 2 + 8 = 11)
 * Worker 2: [4,7] (working time = 4 + 7 = 11)
 * The maximum working time is 11.
 * 
 * Constraints:
 * n == jobs.length
 * 1 <= k <= n <= 12
 * 1 <= jobs[i] <= 107
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution1 {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        // 剪枝1：将工作按耗时从大到小排序，优先分配耗时长的任务，可以尽早触发剪枝条件
        sort(jobs.begin(), jobs.end(), greater<int>());
        int left = jobs[0]; // 最小可能时间：所有工作中最长的那个
        int right = accumulate(jobs.begin(), jobs.end(), 0); // 最大可能时间：所有工作之和（即全部分给一个人）

        // 二分查找最小的可行解
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canFinish(jobs, k, mid)) {
                right = mid; // 如果能完成，尝试更小的 limit
            } else {
                left = mid + 1; // 如果不能完成，增大 limit
            }
        }
        return left;
    }

private:
    bool canFinish(vector<int>& jobs, int k, int limit) {
        vector<int> workloads(k, 0); // 记录每个工人的当前工作量
        return backtrack(jobs, workloads, 0, limit);
    }

    bool backtrack(vector<int>& jobs, vector<int>& workloads, int idx, int limit) {
        if (idx >= jobs.size()) {
            return true; // 所有工作都分配完了
        }
        int curJob = jobs[idx];
        for (int i = 0; i < workloads.size(); ++i) {
            // 剪枝2：如果当前工人加上这个工作会超过 limit，则跳过
            if (workloads[i] + curJob <= limit) {
                workloads[i] += curJob;
                if (backtrack(jobs, workloads, idx + 1, limit)) {
                    return true;
                }
                workloads[i] -= curJob; // 回溯
            }

            // 剪枝3（关键剪枝）：如果当前工人工作量为0，但分配给他后仍然无法找到可行解，
            // 那么后续空闲工人（工作量也是0）也无需尝试，因为工人是无差别的。
            if (workloads[i] == 0) {
                break;
            }
        }
        return false;
    }
};

class Solution2 {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        vector<int> sum(1 << n, 0); // sum[mask] 表示任务子集 mask 的总耗时

        // 1. 预处理所有任务子集的总耗时
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    sum[mask] += jobs[i];
                }
            }
        }

        // dp[i][mask] 表示考虑前 i 个工人，完成工作集合 mask 时，所能达到的「最小最大工作时间」
        vector<vector<int>> dp(k, vector<int>(1 << n, INT_MAX));
        // 初始化：只有 1 个工人的情况
        for (int mask = 0; mask < (1 << n); ++mask) {
            dp[0][mask] = sum[mask];
        }

        // 2. 动态规划
        for (int i = 1; i < k; ++i) {
            for (int mask = 0; mask < (1 << n); ++mask) {
                // 枚举 mask 的子集 sub，作为第 i 个工人完成的任务
                // 优化：使用 sub = (sub - 1) & mask 来枚举子集
                for (int sub = mask; sub; sub = (sub - 1) & mask) {
                    // 第 i 个工人完成 sub 这个子集，剩余的工作 mask - sub 由前 i-1 个工人完成
                    int prevMax = dp[i - 1][mask - sub];
                    int currentMax = max(prevMax, sum[sub]);
                    dp[i][mask] = min(dp[i][mask], currentMax);
                }
            }
        }
        return dp[k - 1][(1 << n) - 1];
    }
};