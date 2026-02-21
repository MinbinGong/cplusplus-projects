/*
 * IPO
 *
 *  Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.
 *
 *  You are given n projects where the ith project has a pure profit profits[i] and a minimum capital of capital[i] is needed to start it.
 *
 *  Initially, you have w capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
 *
 *  Pick a list of at most k distinct projects from given projects to maximize your final capital, and return the final maximized capital.
 *
 *  The answer is guaranteed to fit in a 32-bit signed integer.
 *
 *  Constraints:
 *  1 <= k <= 105
 *  0 <= w <= 109
 *  n == profits.length == capital.length
 *  1 <= n <= 105
 *  -109 <= profits[i] <= 109
 *  0 <= capital[i] <= 109
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<pair<int, int>> projects;
        for (int i = 0; i < n; ++i) {
            projects.emplace_back(capital[i], profits[i]);
        }
        sort(projects.begin(), projects.end()); // 按所需资本升序排列

        priority_queue<int> maxHeap; // 大顶堆，存放当前可投资项目的利润
        int idx = 0;
        for (int i = 0; i < k; ++i) {
            // 将所有所需资本 ≤ 当前资本 w 的项目加入堆
            while (idx < n && projects[idx].first <= w) {
                maxHeap.push(projects[idx].second);
                ++idx;
            }
            if (maxHeap.empty()) break; // 没有可投资项目
            w += maxHeap.top();          // 选择利润最大的项目
            maxHeap.pop();
        }
        return w;
    }
};