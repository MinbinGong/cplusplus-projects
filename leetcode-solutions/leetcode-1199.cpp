/*
 * 1199. Minimum Time to Build Blocks
 *
 * You are given a list of blocks, where blocks[i] = t means that the i-th block needs t units of time to be built. A block can only be built by exactly one worker.
 * 
 * A worker can either split into two workers (number of workers increases by one) or build a block then go home. Both decisions cost some time.
 * 
 * The time cost of spliting one worker into two workers is given as an integer split. Note that if two workers split at the same time, they split in parallel so the cost would be split.
 * 
 * Output the minimum time needed to build all blocks.
 * 
 * Initally, there is only one worker.
 * 
 * Example 1:
 * Input: blocks = [1], split = 1
 * Output: 1
 * Explanation: We use 1 worker to build 1 block in 1 unit of time.
 * 
 * Example 2:
 * Input: blocks = [1,2], split = 5
 * Output: 7
 * Explanation: We split the worker into 2 workers in 5 units of time then assign each of them to a block so the cost is 5 + max(1, 2) = 7.
 * 
 * Example 3:
 * Input: blocks = [1,2,3], split = 1
 * Output: 4
 * Explanation: Split 1 worker into 2, then assign the first worker to the last block.
 * The second worker has to work for 3 units of time.
 * 
 * Note:
 * 1 <= blocks.length <= 10^3
 * 1 <= blocks[i] <= 10^5
 * 1 <= split <= 100
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        // 使用最小堆（优先队列），greater<int> 使得堆顶为最小值
        priority_queue<int, vector<int>, greater<int>> pq;

        // 将所有街区耗时加入堆中
        for (int v : blocks) {
            pq.push(v);
        }

        // 不断合并耗时最短的两个街区
        while (pq.size() > 1) {
            // 弹出最小的两个（x <= y）
            pq.pop();               // 弹出 x（实际并未使用，但需要移除）
            int y = pq.top();       // 获取 y
            pq.pop();               // 弹出 y

            // 合并后新任务的耗时 = y + split
            pq.push(y + split);
        }

        // 堆顶元素即为最终答案
        return pq.top();
    }
};