/**
 * 1383. Maximum Performance of a Team
 * 
 * You are given two integers n and k and two integer arrays speed and efficiency both of length n.
 * There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.
 * 
 * Choose at most k different engineers out of the n engineers to form a team with the maximum performance.
 * 
 * The performance of a team is the sum of their engineers' speeds multiplied by the minimum efficiency among their engineers.
 * 
 * Return the maximum performance of this team. Since the answer can be a huge number, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
 * Output: 60
 * Explanation: We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
 * 
 * Example 2:
 * Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
 * Output: 68
 * Explanation: We have the maximum performance of the team by selecting engineer 1 (with speed=2 and efficiency=5), engineer 2 (with speed=10 and efficiency=4), and engineer 5 (with speed=5 and efficiency=7). That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
 * 
 * Example 3:
 * Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
 * Output: 72
 * 
 * Note:
 * 1 <= n <= 10^5
 * speed.length == n
 * efficiency.length == n
 * 1 <= speed[i] <= 10^5
 * 1 <= efficiency[i] <= 10^8
 * 1 <= k <= n
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        const int MOD = 1e9 + 7;
        
        // Pair each engineer's efficiency and speed
        vector<pair<int, int>> engineers;
        for (int i = 0; i < n; ++i) {
            engineers.emplace_back(efficiency[i], speed[i]);
        }
        
        // Sort by efficiency descending
        sort(engineers.begin(), engineers.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });
        
        // Min‑heap for the speeds of selected engineers
        priority_queue<int, vector<int>, greater<int>> minHeap;
        long long speedSum = 0;
        long long best = 0;
        
        for (const auto& [eff, sp] : engineers) {
            // Add current engineer's speed
            minHeap.push(sp);
            speedSum += sp;
            
            // If we exceed k, remove the smallest speed
            if (minHeap.size() > k) {
                speedSum -= minHeap.top();
                minHeap.pop();
            }
            
            // The current efficiency is the minimum among all chosen because we process in decreasing order
            long long performance = speedSum * eff;
            if (performance > best) {
                best = performance;
            }
        }
        
        return best % MOD;
    }
};