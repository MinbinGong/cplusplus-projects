/**
 * 1834. Single-Threaded CPU
 * https://leetcode.com/problems/single-threaded-cpu/
 * 
 * You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.
 * 
 * You have a single-threaded CPU that can process at most one task at a time and will act in the following way:
 * 
 * If the CPU is idle and there are no available tasks to process, the CPU remains idle.
 * If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
 * Once a task is started, the CPU will process the entire task without stopping.
 * The CPU can finish a task then start a new one instantly.
 * 
 * Return the order in which the CPU will process the tasks.
 * 
 * Example 1:
 * Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
 * Output: [0,2,3,1]
 * Explanation: The events go as follows: 
 * - At time = 1, task 0 is available to process. Available tasks = {0}.
 * - Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
 * - At time = 2, task 1 is available to process. Available tasks = {1}.
 * - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
 * - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
 * - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
 * - At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
 * - At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
 * - At time = 10, the CPU finishes task 1 and becomes idle.
 * 
 * Example 2:
 * Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
 * Output: [4,3,2,0,1]
 * Explanation: The events go as follows:
 * - At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
 * - Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
 * - At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
 * - At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
 * - At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
 * - At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
 * 
 * Constraints:
 * tasks.length == n
 * 1 <= n <= 105
 * 1 <= enqueueTimei, processingTimei <= 109
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        
        // Add original index to each task
        vector<tuple<int, int, int>> tasksWithIndex;
        for (int i = 0; i < n; ++i) {
            tasksWithIndex.emplace_back(tasks[i][0], tasks[i][1], i);
        }
        
        // Sort by enqueue time
        sort(tasksWithIndex.begin(), tasksWithIndex.end());
        
        // Min-heap: (processingTime, index) – smallest processingTime first, then smallest index
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<int> result;
        long long currentTime = 0;
        int idx = 0; // pointer in sorted tasks
        
        while (idx < n || !pq.empty()) {
            // If heap is empty, jump to the next task's arrival
            if (pq.empty()) {
                currentTime = max(currentTime, (long long)get<0>(tasksWithIndex[idx]));
            }
            
            // Push all tasks that have arrived by currentTime
            while (idx < n && get<0>(tasksWithIndex[idx]) <= currentTime) {
                pq.push({get<1>(tasksWithIndex[idx]), get<2>(tasksWithIndex[idx])});
                idx++;
            }
            
            // Process the task with shortest processing time
            auto [proc, originalIndex] = pq.top();
            pq.pop();
            result.push_back(originalIndex);
            currentTime += proc;
        }
        
        return result;
    }
};