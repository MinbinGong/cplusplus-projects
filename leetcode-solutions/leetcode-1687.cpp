/**
 * 1687. Delivering Boxes from Storage to Ports
 * 
 * You have the task of delivering some boxes from storage to their ports using only one ship. However, this ship has a limit on the number of boxes and the total weight that it can carry.
 * 
 * You are given an array boxes, where boxes[i] = [portsi, weighti], and three integers portsCount, maxBoxes, and maxWeight.
 * 
 * portsi is the port where you need to deliver the ith box and weightsi is the weight of the ith box.
 * portsCount is the number of ports.
 * maxBoxes and maxWeight are the respective box and weight limits of the ship.
 * 
 * The boxes need to be delivered in the order they are given. The ship will follow these steps:
 * 
 * The ship will take some number of boxes from the boxes queue, not violating the maxBoxes and maxWeight constraints.
 * For each loaded box in order, the ship will make a trip to the port the box needs to be delivered to and deliver it. If the ship is already at the correct port, no trip is needed, and the box can immediately be delivered.
 * 
 * The ship must end at the last port.
 * 
 * Given boxes, portsCount, maxBoxes, and maxWeight, return the minimum number of trips the ship needs to make to deliver all boxes to their respective ports.
 * 
 * Example 1:
 * Input: boxes = [[1,1],[2,1],[1,1]], portsCount = 2, maxBoxes = 3, maxWeight = 3
 * Output: 4
 * Explanation: The optimal strategy is as follows: 
 * The ship takes all the boxes in the queue, goes to port 1, delivers all the boxes there, and returns to port 2. 
 * The ship takes all the boxes in the queue, goes to port 2, delivers all the boxes there, and returns to port 1.
 * 
 * Example 2:
 * Input: boxes = [[1,2],[3,3],[3,1],[3,1],[2,4]], portsCount = 3, maxBoxes = 3, maxWeight = 6
 * Output: 6
 * Explanation: The optimal strategy is as follows: 
 * The ship takes the first box, goes to port 1, delivers it, and returns to port 3. 
 * The ship takes the second box, goes to port 3, delivers it, and returns to port 1. 
 * The ship takes the third box, goes to port 3, delivers it, and returns to port 1. 
 * The ship takes the fourth box, goes to port 3, delivers it, and returns to port 1. 
 * The ship takes the fifth box, goes to port 2, delivers it, and returns to port 3.
 * 
 * Constraints:
 * 1 <= boxes.length <= 105
 * 1 <= portsCount, maxBoxes, maxWeight <= 105
 * 1 <= portsi <= portsCount
 * 1 <= weightsi <= maxWeight
 * 
 */
#include <vector>
#include <deque>
#include <climits>

using namespace std;

class Solution {
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        if (n == 0) return 0;
        
        // extract port and weight arrays
        vector<int> port(n), weight(n);
        for (int i = 0; i < n; ++i) {
            port[i] = boxes[i][0];
            weight[i] = boxes[i][1];
        }
        
        // prefix sums of weights
        vector<long long> wsum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            wsum[i] = wsum[i - 1] + weight[i - 1];
        }
        
        // differences between consecutive ports
        vector<int> diff(n - 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            diff[i] = (port[i] != port[i + 1]) ? 1 : 0;
        }
        
        // prefix sum of differences: P[i] = number of changes in boxes[0..i-1]
        vector<int> P(n, 0);          // P[0] = 0
        for (int i = 1; i < n; ++i) {
            P[i] = P[i - 1] + diff[i - 1];
        }
        
        const int INF = 1e9;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        
        deque<int> dq;                // stores indices j in increasing order of (dp[j] - P[j])
        dq.push_back(0);              // index 0 is always feasible
        
        int leftBound = 0;             // smallest index that satisfies weight condition for current i
        
        for (int i = 1; i <= n; ++i) {
            // weight constraint: wsum[i] - wsum[j] <= maxWeight  => wsum[j] >= wsum[i] - maxWeight
            long long target = wsum[i] - maxWeight;
            while (leftBound < i && wsum[leftBound] < target) {
                ++leftBound;
            }
            
            // box count constraint: i - j <= maxBoxes  => j >= i - maxBoxes
            int L = max(leftBound, i - maxBoxes);
            if (L < 0) L = 0;          // i - maxBoxes may be negative
            
            // remove indices that are now out of the window
            while (!dq.empty() && dq.front() < L) {
                dq.pop_front();
            }
            
            // compute dp[i] if there is any feasible j
            if (!dq.empty()) {
                int j = dq.front();
                int val = dp[j] - P[j];
                dp[i] = P[i - 1] + 2 + val;
            }
            
            // prepare for future i: insert current index i (if i < n and dp[i] is finite)
            if (dp[i] < INF && i < n) {
                int val_i = dp[i] - P[i];
                while (!dq.empty() && (dp[dq.back()] - P[dq.back()]) >= val_i) {
                    dq.pop_back();
                }
                dq.push_back(i);
            }
        }
        
        return (dp[n] == INF) ? -1 : dp[n];
    }
};