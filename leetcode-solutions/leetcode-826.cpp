/**
 * 826. Most Profit Assigning Work
 *
 * We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job.
 *
 * Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job
 * with difficulty at most worker[i].
 *
 * Every worker can be assigned at most one job, but one job can be completed multiple times.
 *
 * For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete
 * any job, his profit is $0.
 *
 * What is the most profit we can make?
 *
 * Example:
 * Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
 * Output: 100 
 * Explanation: Workers are assigned jobs of difficulty [4,4,6,7] and they get profit of [20,20,30,40] seperately.
 * 
 * Note:
 * 1 <= difficulty.length = profit.length <= 10000
 * 1 <= worker.length <= 10000
 * difficulty[i], profit[i], worker[i]  are in range [1, 10^5]
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size();
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.emplace_back(difficulty[i], profit[i]);
        }
        sort(jobs.begin(), jobs.end()); // 按难度排序

        // 预处理：到当前难度为止的最大利润
        vector<int> maxProfit(n);
        int curMax = 0;
        for (int i = 0; i < n; ++i) {
            curMax = max(curMax, jobs[i].second);
            maxProfit[i] = curMax;
        }

        int total = 0;
        for (int w : worker) {
            // 二分查找最后一个难度 <= w 的工作
            int lo = 0, hi = n - 1, best = -1;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (jobs[mid].first <= w) {
                    best = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (best != -1) {
                total += maxProfit[best];
            }
        }
        return total;
    }
};